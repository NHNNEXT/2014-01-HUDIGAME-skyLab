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

	DDApplication* app = DDApplication::GetInstance();
	GPlayerManager = PlayerManager::Create();
	GSceneManager = SceneManager::Create();
	g_UIManager = UIManager::Create();
	g_GameData = GameData::Create();

	app->Init( L"Debris Defragmentation", 1230, 750 );
	
	DDScene* scene = GSceneManager->CreateScene(L"PlayScene1");	
	
	DDSceneDirector::GetInstance()->ChangeScene( scene );

	app->Run();
	app->Release();

	//SafeDelete( scene );	


#ifdef _DEBUG
	FreeConsole();
#endif

	return 0;
}