#include "stdafx.h"
#include "ClientSession.h"
#include "..\..\PacketType.h"
#include "ClientManager.h"

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
	// �� �о� ���� �θ� �Լ��� ���
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
		if ( mRecvBuffer.GetStoredSize( ) < header.mSize )
			return;

		/// ��Ŷ �ڵ鸵
		switch ( header.mType )
		{
		case PKT_CS_LOGIN:
		{
							 LoginRequest inPacket;
							 mRecvBuffer.Read( (char*)&inPacket, header.mSize );

							 /// �α����� DB �۾��� ���ľ� �ϱ� ������ DB �۾� ��û�Ѵ�.
							 // LoadPlayerDataContext* newDbJob = new LoadPlayerDataContext( mSocket, inPacket.mPlayerId );
							 // GDatabaseJobManager->PushDatabaseJobRequest( newDbJob );

		}
			break;

		

		default:
		{
				   /// ���� ������ �̻��� ��Ŷ �����Ŵ�.
				   Disconnect( );
				   return;
		}
			break;
		}
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

	/// ��? �� ���� ��쵵 �ֳ�? (Ŀ���� send queue�� ��á�ų�, Send Completion������ �� send �� ���?)
	if ( mSendBuffer.GetContiguiousBytes( ) > 0 )
	{
		assert( false );
	}

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

