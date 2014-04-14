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



void ClientSession::LoginDone( int pid, double x, double y, double z, const char* name )
{
	LoginResult outPacket;

	outPacket.mPlayerId = mPlayerId = pid;
	// strcpy_s( mPlayerName, name );
	// strcpy_s( outPacket.mName, name );

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


// 각 패킷을 처리하는 핸들러를 만들자
REGISTER_HANDLER( PKT_CS_LOGIN )
{
	LoginRequest inPacket = static_cast<LoginRequest&>( pktBase );
	session->HandleLoginRequest( inPacket );
}

void ClientSession::HandleLoginRequest( LoginRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	// 로그인 됐으면 아이디 할당해서 보내줘야지
	int playerId = GGameLogic->AddPlayer();
	if ( playerId == -1 )
	{
		// 더 못 들어온다.
		Disconnect();
	}

	// 접속한 아이에게 아이디를 할당해준다.
	LoginResult outPacket;
	outPacket.mPlayerId = playerId;
	SendRequest( &outPacket );

	// 다른 애들에게 플레이어가 추가되었다는 것을 널리 알린다.
	// NewResult 

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}

REGISTER_HANDLER( PKT_CS_ACCELERATION )
{
	AccelerarionRequest inPacket = static_cast<AccelerarionRequest&>( pktBase );
	session->HandleAccelerationRequest( inPacket );
}

void ClientSession::HandleAccelerationRequest( AccelerarionRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	// 이걸 게임 로직에 적용하고 
	// 적용에 문제가 없으면 다른 클라이언트에게 방송!

	AccelerarionResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;

	// 게임 데이터에서 지금 플레이어 관련 데이터 받아와서 넣자
	// 방향은 방향 전환 요청에서만 처리하는 게 좋으려나...

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

	// 이걸 게임 로직에 적용하고 
	// 적용에 문제가 없으면 다른 클라이언트에게 방송!

	StopResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;

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

	// 이걸 게임 로직에 적용하고 
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

	// 요청받은 캐릭터 데이터를 받아와서 방송!

	SyncResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;

	/// 다른 애들도 업데이트 해라
	if ( !Broadcast( &outPacket ) )
	{
		Disconnect();
	}
}