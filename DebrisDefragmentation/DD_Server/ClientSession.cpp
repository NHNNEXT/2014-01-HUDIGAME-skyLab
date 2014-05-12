#include "stdafx.h"
#include "ClientSession.h"
#include "..\..\PacketType.h"
#include "ClientManager.h"
#include "GameOption.h"

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

	printf( "[DEBUG] Client Connected: IP=%s, PORT=%d\n", inet_ntoa( mClientAddr.sin_addr ), ntohs( mClientAddr.sin_port ) );

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
	// 내 캐릭터는 내가 지우고 나가자
	m_ActorManager->DeleteActor( m_Character.GetCharacterId() );
	GClientManager->DeleteSession( mPlayerId, this );

	if ( !IsConnected( ) )
		return;

	printf( "[DEBUG] Client Disconnected: IP=%s, PORT=%d\n", inet_ntoa( mClientAddr.sin_addr ), ntohs( mClientAddr.sin_port ) );

	/// 즉각 해제

	LINGER lingerOption;
	lingerOption.l_onoff = 1;
	lingerOption.l_linger = 0;

	/// no TCP TIME_WAIT
	if ( SOCKET_ERROR == setsockopt( mSocket, SOL_SOCKET, SO_LINGER, (char*)&lingerOption, sizeof( LINGER ) ) )
	{
		printf_s( "[DEBUG] setsockopt linger option error: %d\n", GetLastError( ) );
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
	printf( "DEBUG: Player[%d] Update Done\n", mPlayerId );
}



void ClientSession::LoginDone( int pid )
{
	LoginResult outPacket;

	outPacket.mPlayerId = mPlayerId = pid;
	outPacket.mTeamColor = static_cast<int>( m_Character.GetTeam() );

	GClientManager->RegisterSession( mPlayerId, this );

	SendRequest( &outPacket );

	mLogon = true;
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

	outPacket.mPos = Float3D( m_Character.GetTransform().GetPosition() );
	outPacket.mVelocity = Float3D( m_Character.GetVelocity() );

	// 자신과 연결된 클라이언트와 기타 모든 클라이언트에게 전송
	SendRequest( &outPacket );
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
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
}

void ClientSession::SyncCurrentStatus()
{
	SyncResult outPacket;

	outPacket.mPlayerId = m_Character.GetCharacterId();

	outPacket.mPos = Float3D( m_Character.GetTransform().GetPosition() );
	outPacket.mVelocity = Float3D( m_Character.GetVelocity() );

	// 자신과 연결된 클라이언트와 기타 모든 클라이언트에게 전송
	SendRequest( &outPacket );
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}


void ClientSession::SendCurrentStatus( ClientSession* targetClient )
{
	SyncResult outPacket;

	outPacket.mPlayerId = m_Character.GetCharacterId();

	outPacket.mPos = Float3D( m_Character.GetTransform().GetPosition() );
	outPacket.mVelocity = Float3D( m_Character.GetVelocity() );

	// 인자로 받은 클라이언트에게 내 상태를 저장한 패킷을 전송
	targetClient->SendRequest( &outPacket );
	// GClientManager->DirectSend( targetClientSock, &outPacket );
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

	// 로그인 됐으면 플레이어 만들고
	// pid를 할당 받아야 되는데
	int characterId = m_ActorManager->RegisterUser( &m_Character );
	if ( characterId == -1 )
	{
		// 더 못 들어온다.
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

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	// 내 캐릭터를 다른 플레이어들에게 방송
	NewResult newPlayerPacket;
	newPlayerPacket.mPlayerId = mPlayerId;

	newPlayerPacket.mPos = Float3D( m_Character.GetTransform().GetPosition() );
	newPlayerPacket.mVelocity = Float3D( m_Character.GetVelocity() );
	newPlayerPacket.mRotation = Float3D( m_Character.GetTransform().GetRotation() );

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

	currentIssState.mIssPositionZ = m_ActorManager->GetIssPositionZ();
	currentIssState.mIssVelocityZ = m_ActorManager->GetIssVelocityZ();

	for ( int i = 0; i < MODULE_NUMBER; ++i )
	{
		TeamColor color = TeamColor::NO_TEAM;
		float hp = 1.0f;

		std::tie( color, hp ) = m_ActorManager->GetModuleState( i );

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
	// printf_s( "goforward %d\n", inPacket.mPlayerId ); 

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	// 스킬 사용
	if ( !m_Character.GetClassComponent().GoForward( m_Character.GetViewDirection() ) )
		return;

	AccelerarionResult outPacket;
	outPacket.mPlayerId = mPlayerId;

	outPacket.mPos = Float3D( m_Character.GetTransform().GetPosition() );
	outPacket.mVelocity = Float3D( m_Character.GetVelocity() );
	outPacket.mRotation = Float3D( m_Character.GetTransform().GetRotation() );

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

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	// 이걸 멤버 유저에게 적용하고 - 멈추는 건 자유다
	m_Character.GetClassComponent().Stop( );

	StopResult outPacket;
	outPacket.mPlayerId = mPlayerId;

	// printf_s( "%f / %f / %f\n", position.x, position.y, position.z );

	outPacket.mPos = Float3D( m_Character.GetTransform().GetPosition() );

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

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	// 이걸 멤버 유저에게 적용하고 - 회전도 자유다
	//m_Character.IncreaseRotation( inPacket.mRotationX * MOUSE_ROTATION_WEIGHT, inPacket.mRotationY * MOUSE_ROTATION_WEIGHT, inPacket.mRotationZ );
	// turn body는 increase가 아니라 set을 사용함
	m_Character.GetTransform().SetRotation( inPacket.mRotation.GetD3DVEC() );

	RotationResult outPacket;
	outPacket.mPlayerId = mPlayerId;

	outPacket.mRotation = Float3D( m_Character.GetTransform().GetRotation() );

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

REGISTER_HANDLER( PKT_CS_SKILL_PUSH )
{
	SkillPushRequest inPacket = static_cast<SkillPushRequest&>( pktBase );
	session->HandleSkillPushRequest( inPacket );
}

void ClientSession::HandleSkillPushRequest( SkillPushRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	// 일단 유저가 보내온 값을 적용시켜서 판단할까...적어도 회전 값은 적용하는 것이 맞을 것 같다.
	// 캐릭터에 적용 안 한다. 패킷에 담겨온 회전 정보는 카메라의 회전 정보일뿐 캐릭터의 회전 정보가 아니다.
	// m_Character.SetRotation( inPacket.mRotationX, inPacket.mRotationY, inPacket.mRotationZ );

	// 우선 타겟이 있는지 확인
	int targetId = -1;
	D3DXVECTOR3 spinAxis; 
	
	/// mPlayerId를 보낸 값으로 쓰지 않고, 내가 갖고 있는 값으로 쓰도록 한다... 
	std::tie(targetId, spinAxis) = m_ActorManager->DetectTarget( mPlayerId, inPacket.mRotation.m_X, inPacket.mRotation.m_Y, inPacket.mRotation.m_Z );
	
	// 타겟이 없으면 그냥 무시
	if ( targetId == -1 )
		return;

	// 타겟이 있으면 
	// for debugging
	printf_s( "push target : %d\n", targetId );
	
	Actor* targetCharacter = m_ActorManager->GetActor( targetId );
	D3DXVECTOR3 force = targetCharacter->GetTransform().GetPosition() - m_Character.GetTransform().GetPosition();
	m_Character.GetClassComponent().SkillPush( targetCharacter->GetClassComponent(), force );

	// 원칙적으로 모든 스킬 사용에 의한 결과 반영 작업은 classComponent의 각 스킬 함수 안에서 처리하는 게 좋을 것 같다
	// 그런데 부분적으로 현재 플레이어-액터 안에 있는 변수들의 조작이 필요한 작업들은 여기서 처리하는데..
	// 구조 변경이 필요할지도...
	targetCharacter->SetSpin( spinAxis, DEFAULT_SPIN_ANGULAR_VELOCITY );
	
	SkillPushResult outPacket;
	outPacket.mPlayerId = mPlayerId;
	outPacket.mTargetId = targetId;

	outPacket.mPos = Float3D( targetCharacter->GetTransform().GetPosition() );
	outPacket.mVelocity = Float3D( targetCharacter->GetVelocity() );
	outPacket.mSpinAxis = Float3D( spinAxis );
	outPacket.mForce = Float3D( force );
	outPacket.mSpinAngularVelocity = DEFAULT_SPIN_ANGULAR_VELOCITY;

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

REGISTER_HANDLER( PKT_CS_SKILL_PULL )
{
	SkillPullRequest inPacket = static_cast<SkillPullRequest&>( pktBase );
	session->HandleSkillPullRequest( inPacket );
}

void ClientSession::HandleSkillPullRequest( SkillPullRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	// scout 특수 스킬입니다.
	if ( m_Character.GetClassComponent().GetCharacterClassName() != CharacterClass::STRIKER )
		return;

	// 우선 타겟이 있는지 확인
	int targetId = -1;
	D3DXVECTOR3 spinAxis;

	std::tie( targetId, spinAxis ) = m_ActorManager->DetectTarget( mPlayerId, inPacket.mRotation.m_X, inPacket.mRotation.m_Y, inPacket.mRotation.m_Z );

	// 타겟이 없으면 그냥 무시
	if ( targetId == -1 )
		return;

	// 타겟이 있으면 
	// for debugging
	// printf_s( "pull target : %d\n", targetId );

	Actor* targetCharacter = m_ActorManager->GetActor( targetId );
	D3DXVECTOR3 force = targetCharacter->GetTransform( ).GetPosition( ) - m_Character.GetTransform( ).GetPosition( );
	m_Character.GetClassComponent( ).SkillPull( targetCharacter->GetClassComponent( ), force );

	// 이것도...
	targetCharacter->SetSpin( spinAxis, DEFAULT_SPIN_ANGULAR_VELOCITY );

	SkillPullResult outPacket;
	outPacket.mPlayerId = mPlayerId;
	outPacket.mTargetId = targetId;

	outPacket.mPos = Float3D( targetCharacter->GetTransform().GetPosition() );
	outPacket.mVelocity = Float3D( targetCharacter->GetVelocity() );
	outPacket.mSpinAxis = Float3D( spinAxis );
	outPacket.mForce = Float3D( -force );

	outPacket.mSpinAngularVelocity = 1.0f;

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

REGISTER_HANDLER( PKT_CS_DEAD )
{
	DeadRequest inPacket = static_cast<DeadRequest&>( pktBase );
	session->HandleDeadRequest( inPacket );
}

void ClientSession::HandleDeadRequest( DeadRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );
	
	if ( mPlayerId != inPacket.mPlayerId )
		return;

	// 판단은 서버가 한다! - 이런거 보내지 마라(지금은)
	/*
	// printf_s( "Player %d is Dead\n", inPacket.mPlayerId );
	// 적용에 문제가 없으면 다른 클라이언트에게 방송! - 정지 위치는 서버 좌표 기준
	DeadResult outPacket;
	outPacket.mPlayerId = mPlayerId;

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
	*/
}

REGISTER_HANDLER( PKT_CS_RESPAWN )
{
	RespawnRequest inPacket = static_cast<RespawnRequest&>( pktBase );
	session->HandleRespawnRequest( inPacket );
}

void ClientSession::HandleRespawnRequest( RespawnRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	m_Character.InitTeamPosition();
	
	// printf_s( "Player %d Respawn\n", inPacket.mPlayerId );

	// 조심해!!! 
	// 클래스 추가하고 구현할 때,
	// 받은 패킷에 있는 클래스대로 리스폰시 classComponent변경해줄 것.
	// 05.04 김성환
	// m_Character.ChangeClass( static_cast<CharacterClass>( inPacket.mCharacterClass ) );

	// 적용에 문제가 없으면 다른 클라이언트에게 방송! - 정지 위치는 서버 좌표 기준
	RespawnResult outPacket;
	outPacket.mPlayerId = mPlayerId;
	outPacket.mCharacterClass = inPacket.mCharacterClass;

	outPacket.mPos = Float3D( m_Character.GetTransform().GetPosition() );
	outPacket.mRotation = Float3D( m_Character.GetTransform().GetRotation() );

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

REGISTER_HANDLER( PKT_CS_OCCUPY )
{
	SkillOccupyRequest inPacket = static_cast<SkillOccupyRequest&>( pktBase );
	session->HandleOccupyRequest( inPacket );
}

void ClientSession::HandleOccupyRequest( SkillOccupyRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	// actorManager를 통해서 스킬을 시전하면
	// actorManager는 멤버 변수인 ISS를 통해서 확인하고
	// 소유주 변경에 따른 ISS 속도를 변경하고
	// 세션에 변경 결과 - 모듈이름, 바뀐 소유주, ISS위치, ISS 속도 - 를 반환
	ISSModuleName moduleName = ISSModuleName::NO_MODULE;
	TeamColor teamColor = TeamColor::NO_TEAM;
	float IssPosX = 0.0f;
	float IssVelocityX = 0.0f;

	std::tie( moduleName, teamColor, IssPosX, IssVelocityX ) = m_ActorManager->TryOccupy( inPacket.mPlayerId, inPacket.mRotation.m_X, inPacket.mRotation.m_Y, inPacket.mRotation.m_Z );

	// 변경사항 없으면 리턴
	if ( moduleName == ISSModuleName::NO_MODULE )
		return;

	// 반환받은 결과를 방송!
	SkillOccupyResult outPacket;

	outPacket.mPlayerId = mPlayerId;

	outPacket.mModule = static_cast<int>( moduleName );
	outPacket.mOccupyTeam = static_cast<int>( teamColor );
	outPacket.mIssPositionZ = IssPosX;
	outPacket.mIssVelocityZ = IssVelocityX;

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

REGISTER_HANDLER( PKT_CS_DESTROY )
{
	SkillDestroyRequest inPacket = static_cast<SkillDestroyRequest&>( pktBase );
	session->HandleDestroyRequest( inPacket );
}

void ClientSession::HandleDestroyRequest( SkillDestroyRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	ISSModuleName moduleName = ISSModuleName::NO_MODULE;
	float moduleHP = 1.0f;

	std::tie( moduleName, moduleHP ) = m_ActorManager->TryDestroy( inPacket.mPlayerId, inPacket.mRotation.m_X, inPacket.mRotation.m_Y, inPacket.mRotation.m_Z );

	// 변경사항 없으면 리턴
	if ( moduleName == ISSModuleName::NO_MODULE )
		return;

	// 반환받은 결과를 방송!
	SkillDestroyResult outPacket;

	outPacket.mPlayerId = mPlayerId;

	outPacket.mModule = static_cast<int>( moduleName );
	outPacket.mModuleHP = moduleHP;

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}


REGISTER_HANDLER( PKT_CS_SHARE_FUEL )
{
	ShareFuelRequest inPacket = static_cast<ShareFuelRequest&>( pktBase );
	session->HandleShareFuelRequest( inPacket );
}

void ClientSession::HandleShareFuelRequest( ShareFuelRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	if ( mPlayerId != inPacket.mPlayerId )
		return;

	// 나눠 줄 연료가 없다ㅠ
	if ( m_Character.GetClassComponent( ).GetFuel( ) < DEFAULT_FUEL_SHARE_AMOUNT )
		return;

	int targetId = -1;
	D3DXVECTOR3 spinAxis;

	std::tie( targetId, spinAxis ) = m_ActorManager->DetectTarget( mPlayerId, inPacket.mRotation.m_X, inPacket.mRotation.m_Y, inPacket.mRotation.m_Z );

	// 타겟이 없으면 그냥 무시
	if ( targetId == -1 )
		return;

	m_Character.GetClassComponent().SkillShareFuel( m_ActorManager->GetActor( targetId )->GetClassComponent() );

	// 반환받은 결과를 방송!
	ShareFuelResult outPacket;

	outPacket.mPlayerId = mPlayerId;
	outPacket.mPlayerFuel = m_Character.GetClassComponent().GetFuel();

	outPacket.mTargetId = targetId;
	outPacket.mTargetFuel = m_ActorManager->GetActor( targetId )->GetClassComponent().GetFuel();

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect( );
	}
}