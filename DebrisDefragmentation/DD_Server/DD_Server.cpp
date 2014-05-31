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

#include "LogManager.h"

#pragma comment(lib,"ws2_32.lib")

__declspec( thread ) int LThreadType = -1;

typedef ProducerConsumerQueue<SOCKET, 100> PendingAcceptList;

int _tmain(int argc, _TCHAR* argv[])
{
	// exception 발생 경우 처리
	SetUnhandledExceptionFilter( ExceptionFilter );

	LThreadType = THREAD_MAIN;

	// Manager 생성 - 아직 DB는 사용 안 함
	GClientManager = new ClientManager;
	GClientManager->Init();

	GLogManager = new LogManager;
	GLogManager->Init();

	/// 윈속 초기화
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

	DDLOG_INFO( L"server started" );

	/// listen
	ret = listen( listenSocket, SOMAXCONN );
	if ( ret == SOCKET_ERROR )
		return -1;

	/// accepting list
	PendingAcceptList pendingAcceptList;

	/// Client Logic + I/O Thread
	DWORD dwThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex( NULL, 0, ClientHandlingThread, (LPVOID)&pendingAcceptList, 0, (unsigned int*)&dwThreadId );
	if ( hThread == NULL )
		return -1;

	/// accept loop
	while ( true )
	{
		SOCKET acceptedSocket = accept( listenSocket, NULL, NULL );
		if ( acceptedSocket == INVALID_SOCKET )
		{
			DDLOG_WARN( L"accept: invalid socket" );
			continue;
		}

		pendingAcceptList.Produce( acceptedSocket );
	}

	CloseHandle( hThread );

	// 윈속 종료
	WSACleanup( );

	DDLOG_INFO( L"server closed" );

	// 자원 정리
	delete GClientManager;
	delete GLogManager;

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
	liDueTime.QuadPart = -10000000; ///< 1초 후부터 동작
	if ( !SetWaitableTimer( hTimer, &liDueTime, 100, TimerProc, NULL, TRUE ) )
		return -1;

	while ( true )
	{
		SOCKET acceptSock = NULL;

		/// 새로 접속한 클라이언트 처리
		if ( pAcceptList->Consume( acceptSock, false ) )
		{
			/// 소켓 정보 구조체 할당과 초기화
			ClientSession* client = GClientManager->CreateClient( acceptSock );

			SOCKADDR_IN clientaddr;
			int addrlen = sizeof( clientaddr );
			getpeername( acceptSock, (SOCKADDR*)&clientaddr, &addrlen );

			// 클라 접속 처리
			if ( false == client->OnConnect( &clientaddr ) )
			{
				client->Disconnect();
			}

			continue; ///< 다시 대기로
		}

		/// 최종적으로 클라이언트들에 쌓인 send 요청 처리
		GClientManager->FlushClientSend();

		/// APC Queue에 쌓인 작업들 처리
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
