//	server for Debris defragmentation
//	Choi Gyeongwook	
//	2014. 4. 10

#include "stdafx.h"
#include "DD_Server.h"

#include "Config.h"
#include "..\..\PacketType.h"

#include "ClientManager.h"
#include "ClientSession.h"
#include "Exception.h"
#include "ProducerConsumerQueue.h"

#pragma comment(lib,"ws2_32.lib")

SOCKET g_AcceptedSocket = NULL;
CRITICAL_SECTION g_AcceptedSockLock;
CONDITION_VARIABLE g_SocketFull;
CONDITION_VARIABLE g_SocketEmpty;
bool g_NewSocketFlag;

__declspec( thread ) int LThreadType = -1;

typedef ProducerConsumerQueue<SOCKET, 100> PendingAcceptList;

int _tmain(int argc, _TCHAR* argv[])
{
	// �Ӱ迵�� ���� ���� �ʱ�ȭ 
	InitializeConditionVariable( &g_SocketFull );
	InitializeConditionVariable( &g_SocketEmpty );
	InitializeCriticalSection( &g_AcceptedSockLock );
	g_NewSocketFlag = false;

	// exception �߻� ��� ó��
	SetUnhandledExceptionFilter( ExceptionFilter );

	LThreadType = THREAD_MAIN;

	// Manager ���� - ���� DB�� ��� �� ��
	GClientManager = new ClientManager;

	/// ���� �ʱ�ȭ
	WSADATA wsa;
	if ( WSAStartup( MAKEWORD( 2, 2 ), &wsa ) != 0 )
		return -1;

	SOCKET listenSocket = socket( AF_INET, SOCK_STREAM, 0 );
	if ( listenSocket == INVALID_SOCKET )
		return -1;

	int opt = 1;
	setsockopt( listenSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof( int ) );

	/// bind
	SOCKADDR_IN serveraddr;
	ZeroMemory( &serveraddr, sizeof( serveraddr ) );
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons( LISTEN_PORT );
	serveraddr.sin_addr.s_addr = htonl( INADDR_ANY );
	int ret = bind( listenSocket, (SOCKADDR*)&serveraddr, sizeof( serveraddr ) );
	if ( ret == SOCKET_ERROR )
		return -1;

	/// listen
	ret = listen( listenSocket, SOMAXCONN );
	if ( ret == SOCKET_ERROR )
		return -1;

	/// accepting list
	PendingAcceptList pendingAcceptList;

	/// auto-reset event
	HANDLE hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	if ( hEvent == NULL )
		return -1;

	/// Client Logic + I/O Thread
	DWORD dwThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex( NULL, 0, ClientHandlingThread, hEvent, 0, (unsigned int*)&dwThreadId );
	if ( hThread == NULL )
		return -1;

	/// accept loop
	while ( true )
	{
		SOCKET acceptedSocket = accept( listenSocket, NULL, NULL );
		if ( acceptedSocket == INVALID_SOCKET )
		{
			printf( "accept: invalid socket\n" );
			continue;
		}

		pendingAcceptList.Produce( acceptedSocket );
	}

	CloseHandle( hThread );
	CloseHandle( hEvent );

	// ���� ����
	WSACleanup( );

	delete GClientManager;
	return 0;
}

unsigned int WINAPI ClientHandlingThread( LPVOID lpParam )
{
	LThreadType = THREAD_CLIENT;

	PendingAcceptList* pAcceptList = (PendingAcceptList*)lpParam;

	/// Timer
	HANDLE hTimer = CreateWaitableTimer( NULL, FALSE, NULL );
	if ( hTimer == NULL )
		return -1;

	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = -10000000; ///< 1�� �ĺ��� ����
	if ( !SetWaitableTimer( hTimer, &liDueTime, 100, TimerProc, NULL, TRUE ) )
		return -1;

	while ( true )
	{
		SOCKET acceptSock = NULL;

		/// ���� ������ Ŭ���̾�Ʈ ó��
		if ( pAcceptList->Consume( acceptSock, false ) )
		{
			/// ���� ���� ����ü �Ҵ�� �ʱ�ȭ
			ClientSession* client = GClientManager->CreateClient( acceptSock );

			SOCKADDR_IN clientaddr;
			int addrlen = sizeof( clientaddr );
			getpeername( acceptSock, (SOCKADDR*)&clientaddr, &addrlen );

			// Ŭ�� ���� ó��
			if ( false == client->OnConnect( &clientaddr ) )
			{
				client->Disconnect();
			}

			continue; ///< �ٽ� ����
		}

		/// ���������� Ŭ���̾�Ʈ�鿡 ���� send ��û ó��
		GClientManager->FlushClientSend();

		/// APC Queue�� ���� �۾��� ó��
		SleepEx( INFINITE, TRUE );
	}

	CloseHandle( hTimer );
	return 0;
}

void CALLBACK TimerProc( LPVOID lpArg, DWORD dwTimerLowValue, DWORD dwTimerHighValue )
{
	assert( LThreadType == THREAD_CLIENT );

	GClientManager->OnPeriodWork( );
}
