#include "main.h"
#include "stdafx.h"
#include "DDApplication.h"
#include "PlayScene.h"
#include "GameManager.h"
#include "DDSceneDirector.h"
#include "NetworkManager.h"
#include "PlayerManager.h"
#include "SceneManager.h"
#include "UIManager.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// _CrtSetBreakAlloc( 24262 );
	AllocConsole();
	FILE* console;
	freopen_s( &console, "CONOUT$", "wt", stdout );

	printf_s( "Console Open \n" );
#endif 
	UNREFERENCED_PARAMETER( hInstance );
	UNREFERENCED_PARAMETER( nCmdShow );
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	DDApplication* app = DDApplication::GetInstance();
	g_PlayerManager = PlayerManager::Create();
	g_SceneManager = SceneManager::Create();
	g_UIManager = UIManager::Create();

	app->Init( L"Debris Defragmentation", 600, 600 );
	
	DDScene* scene = g_SceneManager->CreateScene(L"PlayScene1");	
	
	DDSceneDirector::GetInstance()->ChangeScene( scene );

	app->Run();
	app->Release();

	//SafeDelete( scene );	


#ifdef _DEBUG
	FreeConsole();
#endif

	return 0;
}