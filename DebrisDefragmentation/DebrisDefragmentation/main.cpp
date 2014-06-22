#include "stdafx.h"
#include "main.h"
#include "DDApplication.h"
#include "PlayScene.h"
#include "GameManager.h"
#include "DDSceneDirector.h"
#include "NetworkManager.h"
#include "PlayerManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "GameData.h"
#include "Exception.h"
#include "client/windows/handler/exception_handler.h"
#include "client/windows/sender/crash_report_sender.h"
#include "EnvironmentManager.h"

// breakpad test를 위한 강제 crash함수인데 test할 때 말고는 사용하지 않아서 경고발생 -> 경고끔
#pragma warning(disable: 4505)
google_breakpad::ExceptionHandler* handler = nullptr;

namespace {
	static void CrashFunction() {
		Sleep( 200 );
		int *i = reinterpret_cast<int*>( 0x45 );
		*i = 5;  // crash!  
	}
}  // namespace  

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 758 );
	AllocConsole();
	FILE* console;
	freopen_s( &console, "CONOUT$", "wt", stdout );

	printf_s( "Console Open \n" );
#endif 
	UNREFERENCED_PARAMETER( hInstance );
	UNREFERENCED_PARAMETER( nCmdShow );
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	// 예외 처리

	SetUnhandledExceptionFilter( ExceptionFilter );
	// 예외 처리 test 함수
	// CrashFunction();

	DDApplication* app = DDApplication::GetInstance();
	GPlayerManager = PlayerManager::Create();
	GSceneManager = SceneManager::Create();
	GEnvironmentManager = EnvironmentManager::Create();
	GUIManager = UIManager::Create();
	g_GameData = GameData::Create();

	app->Init( L"Debris Defragmentation", 1280, 720 );
	
	DDSceneDirector::GetInstance()->ChangeScene(
		GSceneManager->CreateScene( L"LoadingScene", SceneType::LOADING_SCENE ) );
	
	app->Run();
	app->Release();

	//SafeDelete( scene );	


#ifdef _DEBUG
	FreeConsole();
#endif

	return 0;
}