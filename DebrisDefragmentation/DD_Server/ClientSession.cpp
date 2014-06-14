#include "stdafx.h"
#include "ClientSession.h"
#include "..\..\PacketType.h"
#include "ClientManager.h"
#include "GameOption.h"
#include "GameManager.h"
#include "ObjectTable.h"
#include "Transform.h"
#include "Dispenser.h"
#include "..\DebrisDefragmentation\ObjectManager.h"
#include "InGameEvent.h"

#include "LogManager.h"

typedef void( *HandlerFunc )( ClientSession* session, PacketHeader& pktBase );

static HandlerFunc HandlerTable[PKT_MAX];

// 디폴트 : 굿바이다!
static void DefaultHandler( ClientSession* session, PacketHeader& pktBase )
{
	assert( false );
	session->Disconnect();
}

struct InitializeHandlers
{
	InitializeHandlers()
	{
		for ( int i = 0; i < PKT_MAX; ++i )
			HandlerTable[i] = DefaultHandler;
	}
} _init_handlers_;

struct RegisterHandler

{
	RegisterHandler( int pktType, HandlerFunc handler )
	{
		HandlerTable[pktType] = handler;
	}
};

#define REGISTER_HANDLER(PKT_TYPE)	\
	static void Handler_##PKT_TYPE(ClientSession* session, PacketHeader& pktBase); \
	static RegisterHandler _register_##PKT_TYPE(PKT_TYPE, Handler_##PKT_TYPE); \
	static void Handler_##PKT_TYPE(ClientSession* session, PacketHeader& pktBase)

//@}

bool ClientSession::OnConnect( SOCKADDR_IN* addr )
{
	memcpy( &mClientAddr, addr, sizeof( SOCKADDR_IN ) );

	/// 소켓을 넌블러킹으로 바꾸고
	u_long arg = 1;
	ioctlsocket( mSocket, FIONBIO, &arg );

	/// nagle 알고리즘 끄기
	int opt = 1;
	setsockopt( mSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof( int ) );

	DDLOG_DEBUG( L"Client Connected: IP=" << inet_ntoa( mClientAddr.sin_addr ) << L", PORT=" << ntohs( mClientAddr.sin_port ) );
	// printf( "[DEBUG] Client Connected: IP=%s, PORT=%d\n", inet_ntoa( mClientAddr.sin_addr ), ntohs( mClientAddr.sin_port ) );

	mConnected = true;

	return PostRecv( );
}

bool ClientSession::PostRecv( )
{
	if ( !IsConnected( ) )
		return false;

	DWORD recvbytes = 0;
	DWORD flags = 0;
	WSABUF buf;
	buf.len = (ULONG)mRecvBuffer.GetFreeSpaceSize( );
	buf.buf = (char*)mRecvBuffer.GetBuffer( );

	memset( &mOverlappedRecv, 0, sizeof( OverlappedIO ) );
	mOverlappedRecv.mObject = this;

	/// 비동기 입출력 시작
	// 다 읽어 오면 부를 함수도 등록 - 그리고 그놈이 작업 끝나면 또 날 부르겠지...
	if ( SOCKET_ERROR == WSARecv( mSocket, &buf, 1, &recvbytes, &flags, &mOverlappedRecv, RecvCompletion ) )
	{
		if ( WSAGetLastError( ) != WSA_IO_PENDING )
			return false;
	}

	IncOverlappedRequest( );

	return true;
}

void ClientSession::Disconnect( )
{
	// 여기서 게임 로직에 관련된 작업을 하는 경우
	// 클라에서 접속을 끊으면 한 번 호출되어서 로직에 관련된 자원을 정리하고 mConnected를 false로 바꾼다.
	// 하지만 아직 ClietnManager의 mClientList에 ClientSession은 남아 있는 상태이다
	// 이 ClientSession은 CollectGarbageSessions()이 호출되어야 정리되는데, 주기가 1초이다.
	// 문제는 이 1초라는 시간이 지나기 전에 서버 스레드에서 GClientManager->FlushClientSend()를 실행한다.
	// 아직 mClientList에 ClientSession은 남아 있고, 접속 상태를 false로 바뀌어 있으므로
	// SendFlush() 하다가 false를 반환한다.
	// 그러면 ClietnManager는 다시 접속을 해제하도록 Disconnect( )를 호출하게 되고
	// 다시 로직 관련 자원을 해제하려고 시도한다. 그리고 assert()에서 걸리게 된다.

	if ( !IsConnected( ) )
		return;

	// 내 캐릭터는 내가 지우고 나가자
	m_GameManager->DeregisterCharacter( m_Character.GetCharacterId() );
	GClientManager->DeregisterSession( mPlayerId, this );

	DDLOG_DEBUG( L"Client Disconnected: IP=" << inet_ntoa( mClientAddr.sin_addr ) << L", PORT=" << ntohs( mClientAddr.sin_port ) );
	// printf( "[DEBUG] Client Disconnected: IP=%s, PORT=%d\n", inet_ntoa( mClientAddr.sin_addr ), ntohs( mClientAddr.sin_port ) );

	/// 즉각 해제
	LINGER lingerOption;
	lingerOption.l_onoff = 1;
	lingerOption.l_linger = 0;

	/// no TCP TIME_WAIT
	if ( SOCKET_ERROR == setsockopt( mSocket, SOL_SOCKET, SO_LINGER, (char*)&lingerOption, sizeof( LINGER ) ) )
	{
		DDLOG_WARN( L"setsockopt linger option error: " << GetLastError() );
		// printf_s( "[DEBUG] setsockopt linger option error: %d\n", GetLastError( ) );
		return;
	}

	closesocket( mSocket );

	mConnected = false;
}


void ClientSession::OnRead( size_t len )
{
	mRecvBuffer.Commit( len );

	/// 패킷 파싱하고 처리
	while ( true )
	{
		/// 패킷 헤더 크기 만큼 읽어와보기
		PacketHeader header;
		if ( false == mRecvBuffer.Peek( (char*)&header, sizeof( PacketHeader ) ) )
			return;

		/// 패킷 완성이 되는가? 
		if ( mRecvBuffer.GetStoredSize() < header.mSize )
			return;


		if ( header.mType >= PKT_MAX || header.mType <= PKT_NONE )
		{
			Disconnect();
			return;
		}

		/// packet dispatch...
		// 패킷을 처리하는 핸들러를 이용해서 처리하자
		HandlerTable[header.mType]( this, header );
	}
}

bool ClientSession::SendRequest( PacketHeader* pkt )
{
	if ( !IsConnected( ) )
		return false;

	/// Send 요청은 버퍼에 쌓아놨다가 한번에 보낸다.
	if ( false == mSendBuffer.Write( (char*)pkt, pkt->mSize ) )
	{
		/// 버퍼 용량 부족인 경우는 끊어버림
		Disconnect( );
		return false;
	}

	return true;
}

bool ClientSession::SendFlush( )
{
	if ( !IsConnected( ) )
		return false;

	/// 보낼 데이터가 없으면 그냥 리턴
	if ( mSendBuffer.GetContiguiousBytes( ) == 0 )
		return true;

	DWORD sendbytes = 0;
	DWORD flags = 0;

	WSABUF buf;
	buf.len = (ULONG)mSendBuffer.GetContiguiousBytes( );
	buf.buf = (char*)mSendBuffer.GetBufferStart( );

	memset( &mOverlappedSend, 0, sizeof( OverlappedIO ) );
	mOverlappedSend.mObject = this;

	// 비동기 입출력 시작
	if ( SOCKET_ERROR == WSASend( mSocket, &buf, 1, &sendbytes, flags, &mOverlappedSend, SendCompletion ) )
	{
		if ( WSAGetLastError( ) != WSA_IO_PENDING )
			return false;
	}

	IncOverlappedRequest( );

	return true;
}

void ClientSession::OnWriteComplete( size_t len )
{
	/// 보내기 완료한 데이터는 버퍼에서 제거
	mSendBuffer.Remove( len );
}

bool ClientSession::Broadcast( PacketHeader* pkt )
{
	if ( !SendRequest( pkt ) )
		return false;

	if ( !IsConnected( ) )
		return false;

	GClientManager->BroadcastPacket( this, pkt );

	return true;
}

void ClientSession::OnTick( )
{
	/// 클라별로 주기적으로 해야될 일은 여기에
	SyncCharacterDebugInfo();

	/*
	/// 특정 주기로 DB에 위치 저장
	if ( ++mDbUpdateCount == PLAYER_DB_UPDATE_CYCLE )
	{
		mDbUpdateCount = 0;
		UpdatePlayerDataContext* updatePlayer = new UpdatePlayerDataContext( mSocket, mPlayerId );

		updatePlayer->mPosX = mPosX;
		updatePlayer->mPosY = mPosY;
		updatePlayer->mPosZ = mPosZ;
		strcpy_s( updatePlayer->mComment, "updated_test" ); ///< 일단은 테스트를 위해
		GDatabaseJobManager->PushDatabaseJobRequest( updatePlayer );
	}
	*/
}

void ClientSession::UpdateDone( )
{
	/// 콘텐츠를 넣기 전까지는 딱히 해줄 것이 없다. 단지 테스트를 위해서..
	// printf( "DEBUG: Player[%d] Update Done\n", mPlayerId );
}

void ClientSession::LoginDone( int pid )
{
	LoginResult outPacket;

	outPacket.mPlayerId = mPlayerId = pid;
	outPacket.mTeamColor = static_cast<int>( m_Character.GetTeam() );
	outPacket.mRandomSeed = GObjectTable->GetActorManager()->GetRandomSeed();

	GClientManager->RegisterSession( mPlayerId, this );

	SendRequest( &outPacket );

	mLogon = true;

	DDLOG_INFO( L"[client " << mPlayerId << L"] login successed" );
}

///////////////////////////////////////////////////////////

void CALLBACK RecvCompletion( DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags )
{
	ClientSession* fromClient = static_cast<OverlappedIO*>( lpOverlapped )->mObject;

	fromClient->DecOverlappedRequest( );

	if ( !fromClient->IsConnected( ) )
		return;

	/// 에러 발생시 해당 세션 종료
	if ( dwError || cbTransferred == 0 )
	{
		fromClient->Disconnect( );
		return;
	}

	/// 받은 데이터 처리
	fromClient->OnRead( cbTransferred );

	/// 다시 받기
	// 일종의 재귀?? 아니다... 이런걸 Proactor 패턴이라고 한다.
	// http://en.wikipedia.org/wiki/Proactor_pattern
	if ( false == fromClient->PostRecv( ) )
	{
		fromClient->Disconnect( );
		return;
	}
}

void CALLBACK SendCompletion( DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags )
{
	ClientSession* fromClient = static_cast<OverlappedIO*>( lpOverlapped )->mObject;

	fromClient->DecOverlappedRequest( );

	if ( !fromClient->IsConnected( ) )
		return;

	/// 에러 발생시 해당 세션 종료
	if ( dwError || cbTransferred == 0 )
	{
		fromClient->Disconnect( );
		return;
	}

	fromClient->OnWriteComplete( cbTransferred );

}

void ClientSession::BroadcastCollisionResult()
{
	CollisionResult outPacket;

	outPacket.mPlayerId = m_Character.GetCharacterId();

	outPacket.mPos = m_Character.GetTransform()->GetPosition();
	outPacket.mVelocity = m_Character.GetVelocity();

	// 자신과 연결된 클라이언트와 기타 모든 클라이언트에게 전송
	SendRequest( &outPacket );
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] Collision" );
}

void ClientSession::BroadcastDeadResult()
{
	DeadResult outPacket;

	outPacket.mPlayerId = m_Character.GetCharacterId();

	SendRequest( &outPacket );
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] Dead" );
}

void ClientSession::SyncGhostInfo()
{
	GhostSyncResult outPacket;

	outPacket.mPlayerId = m_Character.GetCharacterId();

	outPacket.mPos = m_Character.GetTransform()->GetPosition();
	outPacket.mVelocity = m_Character.GetVelocity();

	// 자신과 연결된 클라이언트와 기타 모든 클라이언트에게 전송
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

void ClientSession::BroadcastKineticState( bool accelerationFlag, bool spinFlag )
{
	KineticStateResult outPacket;

	outPacket.mPlayerId = mPlayerId;
	outPacket.mPos = m_Character.GetTransform()->GetPosition();
	outPacket.mVelocity = m_Character.GetVelocity();

	outPacket.mIsAccelerate = accelerationFlag;
	if ( accelerationFlag )
	{
		outPacket.mForce = m_Character.GetAcceleration();
	}
	
	outPacket.mIsSpin = spinFlag;	
	if ( spinFlag )
	{
		
		outPacket.mSpinAxis = m_Character.GetSpinAxis();
		outPacket.mSpinAngularVelocity = m_Character.GetSpinAngularVelocity();
	}

	// 자신과 연결된 클라이언트와 기타 모든 클라이언트에게 전송
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect( );
	}
}

void ClientSession::BroadcastCharacterState()
{
	CharacterStateResult outPacket;

	outPacket.mPlayerId = mPlayerId;
	outPacket.mSpeedConstant = m_Character.GetSpeedConstant();
	outPacket.mFuel = m_Character.GetClassComponent()->GetFuel();
	outPacket.mOxygen = m_Character.GetClassComponent()->GetOxygen();
	outPacket.mGlobalCooldownTime = m_Character.GetClassComponent()->GetGlobalCooldown();

	// 자신과 연결된 클라이언트와 기타 모든 클라이언트에게 전송
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

void ClientSession::BroadcastAcceleration()
{
	AccelerarionResult outPacket;
	outPacket.mPlayerId = mPlayerId;

	outPacket.mPos = m_Character.GetTransform()->GetPosition();
	outPacket.mVelocity = m_Character.GetVelocity();
	outPacket.mRotation = m_Character.GetTransform()->GetRotation();

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] Accelerate" );
}

void ClientSession::BroadcastDispenserEffect( bool flag )
{
	DispenserEffectResult outPacket;

	outPacket.mPlayerId = mPlayerId;
	outPacket.mDispenserEffectFlag = flag;
	
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] Dispenser effect" );
}


void ClientSession::BroadcastGatherResult()
{
	GatherResult outPacket;
 
	outPacket.mPlayerId = mPlayerId;
	outPacket.mDebrisIndex = GObjectTable->GetActorManager()->GetGatheredDebris();
	outPacket.mCurrentResource = m_Character.GetClassComponent()->GetResource();

	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] Gather" );
}

void ClientSession::SendCurrentStatus( ClientSession* targetClient )
{
	GhostSyncResult outPacket;

	outPacket.mPlayerId = m_Character.GetCharacterId();

	outPacket.mPos = m_Character.GetTransform()->GetPosition();
	outPacket.mVelocity = m_Character.GetVelocity();

	// 인자로 받은 클라이언트에게 내 상태를 저장한 패킷을 전송
	targetClient->SendRequest( &outPacket );
}

void ClientSession::SendWarning()
{
	WarningResult outPacket;

	outPacket.mEventType = static_cast<int>( m_GameManager->GetEvent()->GetEventType() );
	outPacket.mRemainTime = m_GameManager->GetEvent()->GetRemainTime();

	SendRequest( &outPacket );

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] Warning" );
}

void ClientSession::SyncCharacterDebugInfo()
{
	DebugClientInfoResult outPacket;

	outPacket.mPlayerId = mPlayerId;
	outPacket.mClass = static_cast<int>( m_Character.GetClassComponent()->GetCharacterClassName() );

	outPacket.mPos = m_Character.GetTransform()->GetPosition();
	
	outPacket.mIsSpin = m_Character.IsSpinning();
	outPacket.mIsAccelerate = m_Character.IsAccelerating();

	outPacket.mSpeedConstant = m_Character.GetSpeedConstant();
	outPacket.mAcceleration = m_Character.GetAcceleration();
	outPacket.mVelocity = m_Character.GetVelocity();
	outPacket.mSpinAxis = m_Character.GetSpinAxis();
	outPacket.mSpinAngularVelocity = m_Character.GetSpinAngularVelocity();

	outPacket.mFuel = m_Character.GetClassComponent()->GetFuel();
	outPacket.mOxygen = m_Character.GetClassComponent()->GetOxygen();

	SendRequest( &outPacket );

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] sync debug info" );
}

// 각 패킷을 처리하는 핸들러를 만들자
REGISTER_HANDLER( PKT_CS_LOGIN )
{
	LoginRequest inPacket = static_cast<LoginRequest&>( pktBase );
	session->HandleLoginRequest( inPacket );
}

void ClientSession::HandleLoginRequest( LoginRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] request : " << PKT_CS_LOGIN );

	// 로그인 됐으면 플레이어 만들고
	// pid를 할당 받아야 되는데
	int characterId = m_GameManager->RegisterCharacter( &m_Character );
	if ( characterId == -1 )
	{
		// 더 못 들어온다.
		DDLOG_INFO( L"channel is full" );
		Disconnect();
	}

	m_Character.SetCharacterId( characterId );
	m_Character.Init();
	m_Character.InitTeamPosition();

	// 접속한 아이에게 아이디를 할당해준다.
	LoginDone( characterId );
}

REGISTER_HANDLER( PKT_CS_GAME_STATE )
{
	GameStateRequest inPacket = static_cast<GameStateRequest&>( pktBase );
	session->HandleGameStateRequest( inPacket );
}

// 현재 게임 상태를 모두 전송
void ClientSession::HandleGameStateRequest( GameStateRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] request : " << PKT_CS_GAME_STATE );

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	// 내 캐릭터를 다른 플레이어들에게 방송
	NewResult newPlayerPacket;
	newPlayerPacket.mPlayerId = mPlayerId;

	newPlayerPacket.mPos = m_Character.GetTransform()->GetPosition();
	newPlayerPacket.mVelocity = m_Character.GetVelocity();
	newPlayerPacket.mRotation = m_Character.GetTransform()->GetRotation();

	if ( !Broadcast( &newPlayerPacket ) )
	{
		Disconnect();
	}

	// 다른 캐릭터들 정보 전송
	// 매니저에게 요청하면 매니저는 자신이 가진 애들을 차례대로 불러다가 
	// 매니저는 sock 기준으로 방송할 세션을 지정할 수 있어
	// 요청한 아이에게 각자의 상태를 직접 보내도록(방송말고) 하자
	GClientManager->InitPlayerState( this );

	// 기타 게임 정보 전송
	//GameStateResult outPacket;

	// ISS state
	IssStateResult currentIssState;

	currentIssState.mIssPositionZ = m_GameManager->GetIssPositionZ( );
	currentIssState.mIssVelocityZ = m_GameManager->GetIssVelocityZ( );

	for ( int i = 0; i < MODULE_NUMBER; ++i )
	{
		TeamColor color = TeamColor::NO_TEAM;
		float hp = 1.0f;

		std::tie( color, hp ) = m_GameManager->GetModuleState( i );

		currentIssState.mModuleOwner[i] = static_cast<int>( color );
		currentIssState.mModuleHP[i] = hp;
	}

	SendRequest( &currentIssState );
}

REGISTER_HANDLER( PKT_CS_ACCELERATION )
{
	AccelerarionRequest inPacket = static_cast<AccelerarionRequest&>( pktBase );
	session->HandleAccelerationRequest( inPacket );
}

void ClientSession::HandleAccelerationRequest( AccelerarionRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] request : " << PKT_CS_ACCELERATION );

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	// 스킬 사용
	if ( !m_Character.GetClassComponent()->SkillGoForward( mPlayerId, m_Character.GetViewDirection() ) )
		return;

	AccelerarionResult outPacket;
	outPacket.mPlayerId = mPlayerId;

	outPacket.mPos = m_Character.GetTransform()->GetPosition();
	outPacket.mVelocity = m_Character.GetVelocity();
	outPacket.mRotation = m_Character.GetTransform()->GetRotation();

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

REGISTER_HANDLER( PKT_CS_STOP )
{
	StopRequest inPacket = static_cast<StopRequest&>( pktBase );
	session->HandleStopRequest( inPacket );
}

void ClientSession::HandleStopRequest( StopRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] request : " << PKT_CS_STOP );

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	// 이걸 멤버 유저에게 적용하고 - 멈추는 건 자유다
	m_Character.GetClassComponent()->SkillStop( mPlayerId );

	StopResult outPacket;
	outPacket.mPlayerId = mPlayerId;

	// printf_s( "%f / %f / %f\n", position.x, position.y, position.z );

	outPacket.mPos = m_Character.GetTransform()->GetPosition();

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

REGISTER_HANDLER( PKT_CS_ROTATION )
{
	RotationRequest inPacket = static_cast<RotationRequest&>( pktBase );
	session->HandleRotationRequest( inPacket );
}

void ClientSession::HandleRotationRequest( RotationRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] request : " << PKT_CS_ROTATION );

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	// 이걸 멤버 유저에게 적용하고 - 회전도 자유다
	//m_Character.IncreaseRotation( inPacket.mRotationX * MOUSE_ROTATION_WEIGHT, inPacket.mRotationY * MOUSE_ROTATION_WEIGHT, inPacket.mRotationZ );
	// turn body는 increase가 아니라 set을 사용함
	m_Character.GetTransform()->SetRotation( inPacket.mRotation );

	RotationResult outPacket;
	outPacket.mPlayerId = mPlayerId;

	outPacket.mRotation = m_Character.GetTransform()->GetRotation();

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

REGISTER_HANDLER( PKT_CS_RESPAWN )
{
	RespawnRequest inPacket = static_cast<RespawnRequest&>( pktBase );
	session->HandleRespawnRequest( inPacket );
}

void ClientSession::HandleRespawnRequest( RespawnRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] request : " << PKT_CS_RESPAWN );

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	m_Character.InitTeamPosition();
	
	// printf_s( "Player %d Respawn\n", inPacket.mPlayerId );

	// 조심해!!! 
	// 클래스 추가하고 구현할 때,
	// 받은 패킷에 있는 클래스대로 리스폰시 classComponent변경해줄 것.
	// m_Character.ChangeClass( static_cast<CharacterClass>( inPacket.mCharacterClass ) );

	// 적용에 문제가 없으면 다른 클라이언트에게 방송! - 정지 위치는 서버 좌표 기준
	RespawnResult outPacket;
	outPacket.mPlayerId = mPlayerId;
	outPacket.mCharacterClass = inPacket.mCharacterClass;

	// 캐릭터의 모든 값을 초기화
	m_Character.GetClassComponent()->ResetStatus();

	outPacket.mPos = m_Character.GetTransform()->GetPosition();
	outPacket.mRotation = m_Character.GetTransform()->GetRotation();

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

REGISTER_HANDLER( PKT_CS_USING_SKILL )
{
	UsingSkillRequest inPacket = static_cast<UsingSkillRequest&>( pktBase );
	session->HandleUsingSkillRequest( inPacket );
}

void ClientSession::HandleUsingSkillRequest( UsingSkillRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] using skill : " << static_cast<int>( inPacket.mSkill ) );

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	// 스킬 시전!
	if ( !m_Character.GetClassComponent()->UseSkill( inPacket.mSkill, mPlayerId, inPacket.mDirection ) )
		return;

	// 스킬이 적용된 대상은 스킬을 실행하는 과정에서 방송하도록 함

	// 난 내가 쓴 스킬에 대해서 방송한다.
	UsingSkillResult outPacket;
	outPacket.mPlayerId = mPlayerId;
	outPacket.mSkill = inPacket.mSkill;

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

REGISTER_HANDLER( PKT_CS_CHANGE_CLASS )
{
	ChangeClassRequest inPacket = static_cast<ChangeClassRequest&>( pktBase );
	session->HandleChangeClassRequest( inPacket );
}

void ClientSession::HandleChangeClassRequest( ChangeClassRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	DDLOG_DEBUG( L"[client " << mPlayerId << L"] request : " << PKT_CS_CHANGE_CLASS );

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	m_Character.ChangeClass( static_cast<CharacterClass>( inPacket.mNewClass ) );

	// 난 내가 쓴 스킬에 대해서 방송한다.
	ChangeClassResult outPacket;
	outPacket.mPlayerId = mPlayerId;
	outPacket.mNewClass = inPacket.mNewClass;

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}