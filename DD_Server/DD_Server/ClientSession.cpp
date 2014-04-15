#include "stdafx.h"
#include "ClientSession.h"
#include "..\..\PacketType.h"
#include "ClientManager.h"

typedef void( *HandlerFunc )( ClientSession* session, PacketHeader& pktBase );

static HandlerFunc HandlerTable[PKT_MAX];

// ����Ʈ : �¹��̴�!
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

	/// ������ �ͺ�ŷ���� �ٲٰ�
	u_long arg = 1;
	ioctlsocket( mSocket, FIONBIO, &arg );

	/// nagle �˰��� ����
	int opt = 1;
	setsockopt( mSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof( int ) );

	printf( "[DEBUG] Client Connected: IP=%s, PORT=%d\n", inet_ntoa( mClientAddr.sin_addr ), ntohs( mClientAddr.sin_port ) );

	mConnected = true;

	// �α��� ������ �÷��̾� �����
	int playerId = GGameLogic->AddPlayer();
	if ( playerId == -1 )
	{
		// �� �� ���´�.
		Disconnect();
	}

	// ������ ���̿��� ���̵� �Ҵ����ش�.
	LoginDone( playerId );

	// ���� �� ģ���� �����ϱ� ��ü���� ���� ���� ���¸� �� �� ����ȭ �϶�� ��Ų��.
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

	/// �񵿱� ����� ����
	// �� �о� ���� �θ� �Լ��� ��� - �׸��� �׳��� �۾� ������ �� �� �θ�����...
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

	/// �ﰢ ����

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

	/// ��Ŷ �Ľ��ϰ� ó��
	while ( true )
	{
		/// ��Ŷ ��� ũ�� ��ŭ �о�ͺ���
		PacketHeader header;
		if ( false == mRecvBuffer.Peek( (char*)&header, sizeof( PacketHeader ) ) )
			return;

		/// ��Ŷ �ϼ��� �Ǵ°�? 
		if ( mRecvBuffer.GetStoredSize() < header.mSize )
			return;


		if ( header.mType >= PKT_MAX || header.mType <= PKT_NONE )
		{
			Disconnect();
			return;
		}

		/// packet dispatch...
		// ��Ŷ�� ó���ϴ� �ڵ鷯�� �̿��ؼ� ó������
		HandlerTable[header.mType]( this, header );
	}
}

bool ClientSession::SendRequest( PacketHeader* pkt )
{
	if ( !IsConnected( ) )
		return false;

	/// Send ��û�� ���ۿ� �׾Ƴ��ٰ� �ѹ��� ������.
	if ( false == mSendBuffer.Write( (char*)pkt, pkt->mSize ) )
	{
		/// ���� �뷮 ������ ���� �������
		Disconnect( );
		return false;
	}

	return true;
}

bool ClientSession::SendFlush( )
{
	if ( !IsConnected( ) )
		return false;

	/// ���� �����Ͱ� ������ �׳� ����
	if ( mSendBuffer.GetContiguiousBytes( ) == 0 )
		return true;

	DWORD sendbytes = 0;
	DWORD flags = 0;

	WSABUF buf;
	buf.len = (ULONG)mSendBuffer.GetContiguiousBytes( );
	buf.buf = (char*)mSendBuffer.GetBufferStart( );

	memset( &mOverlappedSend, 0, sizeof( OverlappedIO ) );
	mOverlappedSend.mObject = this;

	// �񵿱� ����� ����
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
	/// ������ �Ϸ��� �����ʹ� ���ۿ��� ����
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
	/// Ŭ�󺰷� �ֱ������� �ؾߵ� ���� ���⿡
	/*
	/// Ư�� �ֱ�� DB�� ��ġ ����
	if ( ++mDbUpdateCount == PLAYER_DB_UPDATE_CYCLE )
	{
		mDbUpdateCount = 0;
		UpdatePlayerDataContext* updatePlayer = new UpdatePlayerDataContext( mSocket, mPlayerId );

		updatePlayer->mPosX = mPosX;
		updatePlayer->mPosY = mPosY;
		updatePlayer->mPosZ = mPosZ;
		strcpy_s( updatePlayer->mComment, "updated_test" ); ///< �ϴ��� �׽�Ʈ�� ����
		GDatabaseJobManager->PushDatabaseJobRequest( updatePlayer );
	}
	*/
}


void ClientSession::UpdateDone( )
{
	/// �������� �ֱ� �������� ���� ���� ���� ����. ���� �׽�Ʈ�� ���ؼ�..
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

	/// ���� �߻��� �ش� ���� ����
	if ( dwError || cbTransferred == 0 )
	{
		fromClient->Disconnect( );
		return;
	}

	/// ���� ������ ó��
	fromClient->OnRead( cbTransferred );

	/// �ٽ� �ޱ�
	// ������ ���??
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

	/// ���� �߻��� �ش� ���� ����
	if ( dwError || cbTransferred == 0 )
	{
		fromClient->Disconnect( );
		return;
	}

	fromClient->OnWriteComplete( cbTransferred );

}


// �� ��Ŷ�� ó���ϴ� �ڵ鷯�� ������
REGISTER_HANDLER( PKT_CS_LOGIN )
{
	LoginRequest inPacket = static_cast<LoginRequest&>( pktBase );
	session->HandleLoginRequest( inPacket );
}

// ������ ���Ӱ� ���ÿ� ���� ���� ó���ϹǷ� ������ ���� - ���߿� ����� ���� ��ɰ��� �� ������ ���
void ClientSession::HandleLoginRequest( LoginRequest& inPacket )
{
	mRecvBuffer.Read( (char*)&inPacket, inPacket.mSize );

	// �α��� ������ �÷��̾� �����
	int playerId = GGameLogic->AddPlayer();
	if ( playerId == -1 )
	{
		// �� �� ���´�.
		Disconnect();
	}

	// ������ ���̿��� ���̵� �Ҵ����ش�.
	LoginDone( playerId );

	// ���� �� ģ���� �����ϱ� ��ü���� ���� ���� ���¸� �� �� ����ȭ �϶�� ��Ų��.
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

	// �̰� ���� ������ �����ϰ� 
	if ( !GGameLogic->SetRotation( inPacket.mPlayerId, inPacket.mRotationX, inPacket.mRotationY, inPacket.mRotationZ ) )
	{
		return;
	}

	if ( !GGameLogic->SetAcceleration( inPacket.mPlayerId ) )
	{
		return;
	}

	// ���뿡 ������ ������ �ٸ� Ŭ���̾�Ʈ���� ���!
	AccelerarionResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;

	outPacket.mRotationX = inPacket.mRotationX;
	outPacket.mRotationY = inPacket.mRotationY;
	outPacket.mRotationZ = inPacket.mRotationZ;

	/// �ٸ� �ֵ鵵 ������Ʈ �ض�
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

	// �̰� ���� ������ �����ϰ� 
	if ( !GGameLogic->Stop( inPacket.mPlayerId ) )
	{
		return;
	}

	DDVECTOR3 position = GGameLogic->GetPosition( inPacket.mPlayerId );

	// ���뿡 ������ ������ �ٸ� Ŭ���̾�Ʈ���� ���! - ���� ��ġ�� ���� ��ǥ ����
	StopResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;

	outPacket.mPosX = position.x;
	outPacket.mPosY = position.y;
	outPacket.mPosZ = position.z;

	/// �ٸ� �ֵ鵵 ������Ʈ �ض�
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

	// �̰� ���� ������ �����ϰ� 
	if ( !GGameLogic->SetRotation( inPacket.mPlayerId, inPacket.mRotationX, inPacket.mRotationY, inPacket.mRotationZ ) )
	{
		return;
	}

	// ���뿡 ������ ������ �ٸ� Ŭ���̾�Ʈ���� ���!
	RotationResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;

	outPacket.mRotationX = inPacket.mRotationX;
	outPacket.mRotationY = inPacket.mRotationY;
	outPacket.mRotationZ = inPacket.mRotationZ;

	/// �ٸ� �ֵ鵵 ������Ʈ �ض�
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

	// ��ũ ��û�� ���� ��ü ����ȭ
	GClientManager->SyncAll();
}