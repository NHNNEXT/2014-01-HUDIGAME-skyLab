//	server for Debris defragmentation
//	Choi Gyeongwook	
//	2014. 4. 10

#include "stdafx.h"
#include "DD_Server.h"

#include "ClientManager.h"
#include "DatabaseJobManager.h"
#include "Exception.h"

#pragma comment(lib,"ws2_32.lib")

SOCKET g_AcceptedSocket = NULL;

__declspec( thread ) int LThreadType = -1;

int _tmain(int argc, _TCHAR* argv[])
{
	// exception �߻� ��� ó��
	SetUnhandledExceptionFilter( ExceptionFilter );

	LThreadType = THREAD_MAIN;

	// Manager ���� - ���� DB�� ��� �� ��
	// GClientManager = new ClientManager;
	GDatabaseJobManager = new DatabaseJobManager;


	return 0;
}

