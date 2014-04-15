#include "stdafx.h"
#include "DDNetwork.h"
#include "DDApplication.h"

DDNetwork* GDDNetwork = nullptr;

DDNetwork::DDNetwork( ) :
m_RecvBuffer( DDCircularBuffer( 1024 * 10 ) ),
m_SendBuffer( DDCircularBuffer( 1024 * 10 ) )
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

	if ( SOCKET_ERROR == connect( m_Socket, (LPSOCKADDR)( &SockAddr ), sizeof( SockAddr ) ) )
	{
		if ( GetLastError( ) != WSAEWOULDBLOCK )
			return false;
	}


	return true;
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

		m_PacketHandler[header.mType]->HandlingPacket( header.mType, &m_RecvBuffer, &header );
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

void DDNetwork::SetPacketHandler( short packetType, DDPacketHandler* handler )
{
	m_PacketHandler[packetType] = handler;
}