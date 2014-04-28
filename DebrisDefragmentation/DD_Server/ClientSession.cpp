#include "stdafx.h"
#include "ClientSession.h"
#include "..\..\PacketType.h"
#include "ClientManager.h"

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

	// 로그인 됐으면 플레이어 만들고
	// pid를 할당 받아야 되는데
	int characterId = m_ActorManager->RegisterUser( &m_Character );
	if ( characterId == -1 )
	{
		// 더 못 들어온다.
		Disconnect();
	}

	m_Character.SetcharacterId( characterId );
	m_Character.Init();

	// 접속한 아이에게 아이디를 할당해준다.
	LoginDone( characterId );

	// 새로 온 친구가 있으니까 전체에게 지금 게임 상태를 한 번 동기화 하라고 시킨다.
	GClientManager->SyncAll();

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
	m_ActorManager->DeleteActor( m_Character.GetcharacterId() );

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
	// 일종의 재귀??
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

void ClientSession::SyncCurrentStatus()
{
	SyncResult outPacket;

	D3DXVECTOR3 position = m_Character.GetPosition();
	D3DXVECTOR3 rotation = m_Character.GetRotation();
	D3DXVECTOR3 velocity = m_Character.GetVelocity();

	outPacket.mPlayerId = m_Character.GetcharacterId();

	// 조심해!!
	// 패킷 내부 변수를 아예 벡터로 만들어서 한 번에 복사하자
	outPacket.mPosX = position.x;
	outPacket.mPosY = position.y;
	outPacket.mPosZ = position.z;

	// outPacket.mRotationX = rotation.x;
	// outPacket.mRotationY = rotation.y;
	// outPacket.mRotationZ = rotation.z;

	outPacket.mVelocityX = velocity.x;
	outPacket.mVelocityY = velocity.y;
	outPacket.mVelocityZ = velocity.z;

	// 자신과 연결된 클라이언트와 기타 모든 클라이언트에게 전송
	SendRequest( &outPacket );
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

// 각 패킷을 처리하는 핸들러를 만들자
REGISTER_HANDLER( PKT_CS_LOGIN )
{
	LoginRequest inPacket = static_cast<LoginRequest&>( pktBase );
	session->HandleLoginRequest( inPacket );
}

// 지금은 접속과 동시에 같은 일을 처리하므로 쓰이지 않음 - 나중에 사용자 인증 기능같은 거 넣으면 사용
void ClientSession::HandleLoginRequest( LoginRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	// 로그인 됐으면 플레이어 만들고
	int characterId = m_ActorManager->RegisterUser( &m_Character );
	if ( characterId == -1 )
	{
		// 더 못 들어온다.
		Disconnect();
	}

	m_Character.SetcharacterId( characterId );

	// 접속한 아이에게 아이디를 할당해준다.
	LoginDone( characterId );

	// 새로 온 친구가 있으니까 전체에게 지금 게임 상태를 한 번 동기화 하라고 시킨다.
	GClientManager->SyncAll();
}

REGISTER_HANDLER( PKT_CS_ACCELERATION )
{
	AccelerarionRequest inPacket = static_cast<AccelerarionRequest&>( pktBase );
	session->HandleAccelerationRequest( inPacket );
}

void ClientSession::HandleAccelerationRequest( AccelerarionRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	// 이걸 멤버 유저에게 적용하고 
	m_Character.SetRotation( inPacket.mRotationX, inPacket.mRotationY, inPacket.mRotationZ );
	m_Character.GoForward();

	D3DXVECTOR3 position = m_Character.GetPosition();
	// 적용에 문제가 없으면 다른 클라이언트에게 방송!
	AccelerarionResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;

	outPacket.mPosX = position.x;
	outPacket.mPosY = position.y;
	outPacket.mPosZ = position.z;

	outPacket.mRotationX = inPacket.mRotationX;
	outPacket.mRotationY = inPacket.mRotationY;
	outPacket.mRotationZ = inPacket.mRotationZ;

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

	// 이걸 멤버 유저에게 적용하고 
	m_Character.Stop();

	D3DXVECTOR3 position = m_Character.GetPosition();
	// 적용에 문제가 없으면 다른 클라이언트에게 방송! - 정지 위치는 서버 좌표 기준
	StopResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;

	// printf_s( "%f / %f / %f\n", position.x, position.y, position.z );

	outPacket.mPosX = position.x;
	outPacket.mPosY = position.y;
	outPacket.mPosZ = position.z;

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

	// 이걸 멤버 유저에게 적용하고  
	//m_Character.IncreaseRotation( inPacket.mRotationX * MOUSE_ROTATION_WEIGHT, inPacket.mRotationY * MOUSE_ROTATION_WEIGHT, inPacket.mRotationZ );
	// turn body는 increase가 아니라 set을 사용함
	m_Character.SetRotation( inPacket.mRotationX, inPacket.mRotationY, inPacket.mRotationZ );

	// 적용에 문제가 없으면 다른 클라이언트에게 방송!
	RotationResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;

	outPacket.mRotationX = inPacket.mRotationX;
	outPacket.mRotationY = inPacket.mRotationY;
	outPacket.mRotationZ = inPacket.mRotationZ;

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

REGISTER_HANDLER( PKT_CS_SYNC )
{
	SyncRequest inPacket = static_cast<SyncRequest&>( pktBase );
	session->HandleSyncRequest( inPacket );
}

void ClientSession::HandleSyncRequest( SyncRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	// 싱크 요청이 오면 전체 동기화
	GClientManager->SyncAll();
}

REGISTER_HANDLER( PKT_CS_SKILL_PUSH )
{
	SkillPushRequest inPacket = static_cast<SkillPushRequest&>( pktBase );
	session->HandleSkillPushRequest( inPacket );
}

void ClientSession::HandleSkillPushRequest( SkillPushRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	// 일단 유저가 보내온 값을 적용시켜서 판단할까...적어도 회전 값은 적용하는 것이 맞을 것 같다.
	m_Character.SetRotation( inPacket.mRotationX, inPacket.mRotationY, inPacket.mRotationZ );

	// 우선 타겟이 있는지 확인
	int targetId = m_ActorManager->DetectTarget( inPacket.mPlayerId );
	
	// 타겟이 없으면 그냥 무시
	if ( targetId == -1 )
		return;

	// 타겟이 있으면 
	// for debugging
	printf_s( "target : %d\n", targetId );
	Actor* targetCharacter = m_ActorManager->GetActor( targetId );

	targetCharacter->SetAccelerarion( targetCharacter->GetPosition() - m_Character.GetPosition() );
	
	// 적용에 문제가 없으면 다른 클라이언트에게 방송!
	SkillPushResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;
	outPacket.mTargetId = targetId;

	D3DXVECTOR3 position = targetCharacter->GetPosition();
	outPacket.mPosX = position.x;
	outPacket.mPosY = position.y;
	outPacket.mPosZ = position.z;

	D3DXVECTOR3 velocity = targetCharacter->GetVelocity();
	outPacket.mVelocityX = velocity.x;
	outPacket.mVelocityY = velocity.y;
	outPacket.mVelocityZ = velocity.z;

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

	// 일단 유저가 보내온 값을 적용시켜서 판단할까...적어도 회전 값은 적용하는 것이 맞을 것 같다.
	m_Character.SetRotation( inPacket.mRotationX, inPacket.mRotationY, inPacket.mRotationZ );

	// 우선 타겟이 있는지 확인
	int targetId = m_ActorManager->DetectTarget( inPacket.mPlayerId );

	// 타겟이 없으면 그냥 무시
	if ( targetId == -1 )
		return;

	// 타겟이 있으면 
	// for debugging
	printf_s( "target : %d\n", targetId );
	Actor* targetCharacter = m_ActorManager->GetActor( targetId );

	targetCharacter->SetAccelerarion( m_Character.GetPosition() - targetCharacter->GetPosition() );

	// 적용에 문제가 없으면 다른 클라이언트에게 방송!
	SkillPushResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;
	outPacket.mTargetId = targetId;

	D3DXVECTOR3 position = targetCharacter->GetPosition();
	outPacket.mPosX = position.x;
	outPacket.mPosY = position.y;
	outPacket.mPosZ = position.z;

	D3DXVECTOR3 velocity = targetCharacter->GetVelocity();
	outPacket.mVelocityX = velocity.x;
	outPacket.mVelocityY = velocity.y;
	outPacket.mVelocityZ = velocity.z;

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}