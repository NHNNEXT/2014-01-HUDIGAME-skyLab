#include "stdafx.h"
#include "DDNetwork.h"
#include "DDApplication.h"
#include "DDPacketHeader.h"

DDNetwork::DDNetwork( ) :
m_RecvBuffer( DDCircularBuffer( BUFSIZE ) ),
m_SendBuffer( DDCircularBuffer( BUFSIZE ) )
{
}

DDNetwork::~DDNetwork()
{
}

bool DDNetwork::Init( )
{
	// network init!
	WSADATA WsaDat;

	int nResult = WSAStartup( MAKEWORD( 2, 2 ), &WsaDat );
	if ( nResult != 0 )
		return false;

	m_Socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( m_Socket == INVALID_SOCKET )
		return false;

	nResult = WSAAsyncSelect( m_Socket, DDApplication::GetInstance( )->GetHWND( ), WM_SOCKET, ( FD_CLOSE | FD_CONNECT ) );
	if ( nResult )
	{
		return false;
	}

	HandleInit();

	return true;
}

bool DDNetwork::Release()
{
	return true;
}

bool DDNetwork::Connect( const char* serverIP = "localhost", int port = 9001)
{
	// Resolve IP address for hostname
	struct hostent* host;

	if ( ( host = gethostbyname( serverIP ) ) == NULL )
		return false;

	// Set up our socket address structure
	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons( port );
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *( (unsigned long*)host->h_addr );

	if ( SOCKET_ERROR != connect( m_Socket, (LPSOCKADDR)( &SockAddr ), sizeof( SockAddr ) ) )
	{
		if ( GetLastError( ) != WSAEWOULDBLOCK )
			return false;
	}


	return true;
}

void DDNetwork::Disconnect()
{
	// Á¢¼ÓÀ» ²÷½À´Ï´Ù.
}

/// ÆÐÅ¶Ã³¸® 
void DDNetwork::ProcessPacket( )
{
	while ( true )
	{
		DDPacketHeader header;

		if ( m_RecvBuffer.Peek( (char*)&header, sizeof( DDPacketHeader ) ) == false )
		{
			break;
		}

		if ( header.mSize > m_RecvBuffer.GetCurrentSize( ) ) /// warning
		{
			break;
		}

		m_HandlerTable[header.mType]( header );
	}
}

void DDNetwork::Write( const char* data, size_t size )
{
	if ( m_SendBuffer.Write( data, size ) )
	{
		PostMessage( DDApplication::GetInstance( )->GetHWND( ), WM_SOCKET, NULL, FD_WRITE );
	}
}

void DDNetwork::Read( )
{
	char inBuf[4096] = { 0, };

	int recvLen = recv( m_Socket, inBuf, 4096, 0 );

	if ( !m_RecvBuffer.Write( inBuf, recvLen ) )
	{
		/// ¹öÆÛ ²ËÃ¡´Ù. 
		//assert(false) ;
	}
	else
	{
		ProcessPacket( );
	}
}

void DDNetwork::DefaultHandler( DDPacketHeader& pktBase )
{
	DDNetwork::GetInstance()->Disconnect();
}

void DDNetwork::HandleInit()
{
	for ( int i = 0; i < 1024; ++i )
		m_HandlerTable[i] = DefaultHandler;
}

void DDNetwork::RegisterHandler( int pktType, HandlerFunc handler )
{
	m_HandlerTable[pktType] = handler;
}
