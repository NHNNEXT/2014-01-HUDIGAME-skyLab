#include "stdafx.h"
#include "DDNetwork.h"
#include "DDApplication.h"
#include "DDPacketHeader.h"

DDNetwork::DDNetwork( ) :
m_RecvBuffer( DDCircularBuffer( BUFFER_SIZE ) ),
m_SendBuffer( DDCircularBuffer( BUFFER_SIZE ) )
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
	// ������ �����ϴ�.
 	closesocket( m_Socket );
 	WSACleanup();
}

void DDNetwork::Write( const char* data, size_t size )
{
	if ( m_SendBuffer.Write( data, size ) )
	{
		PostMessage( DDApplication::GetInstance( )->GetHWND( ), WM_SOCKET, NULL, FD_WRITE );
	}
}


void DDNetwork::NagleOff()
{
	/// NAGLE ����
	/// NAGLE Algorithm
	/// http://en.wikipedia.org/wiki/Nagle's_algorithm
	int opt = 1;
	::setsockopt( m_Socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof( int ) );

	int nResult = WSAAsyncSelect( m_Socket, DDApplication::GetInstance()->GetHWND(), WM_SOCKET, ( FD_CLOSE | FD_READ | FD_WRITE ) );
	if ( nResult )
	{
		assert( false );
	}
}


bool DDNetwork::Read()
{
	char inBuf[BUFFER_SIZE] = { 0, };

	int recvLen = recv( m_Socket, inBuf, BUFFER_SIZE, 0 );

	if ( !m_RecvBuffer.Write( inBuf, recvLen ) )
	{
		/// ���� ��á��. 
		//assert(false) ;
		return false;
	}

	return true;
// 	else
// 	{
// 		ProcessPacket( );
// 	}
}


void DDNetwork::Send()
{
	int size = m_SendBuffer.GetCurrentSize();
	if ( size > 0 )
	{
		// ���ۿ��� ������ ��������
		char* data = new char[size];
		m_SendBuffer.Peek( data );

		// �����͸� ������.
		int sent = send( m_Socket, data, size, 0 );

		/// ���ۿ��� ������ �����Ϳ� ���� �������� ũ�Ⱑ �ٸ��� �ִ�
		if ( sent != size )
		{
			OutputDebugStringA( "sent != request\n" );			
		}

		/// ���� ����
		m_SendBuffer.Consume( sent );

		delete[] data;
	}
}


/// ��Ŷó�� 
void DDNetwork::ProcessPacket()
{
	while ( true )
	{
		DDPacketHeader header;

		if ( m_RecvBuffer.Peek( (char*)&header, sizeof( DDPacketHeader ) ) == false )
		{
			break;
		}

		if ( header.mSize > m_RecvBuffer.GetCurrentSize() ) /// warning
		{
			break;
		}

		m_HandlerTable[header.mType]( header );
	}
}

void DDNetwork::DefaultHandler( DDPacketHeader& pktBase )
{
	DDNetwork::GetInstance()->Disconnect();
}

void DDNetwork::HandleInit()
{
	for ( int i = 0; i < MAX_PACKET_SIZE; ++i )
		m_HandlerTable[i] = DefaultHandler;
}

void DDNetwork::RegisterHandler( int pktType, HandlerFunc handler )
{
	m_HandlerTable[pktType] = handler;
}
