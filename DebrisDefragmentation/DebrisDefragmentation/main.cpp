#include "main.h"
#include "stdafx.h"
#include "DDApplication.h"
#include "PlayScene.h"
#include "GameManager.h"
#include "DDSceneDirector.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( );

#endif 
	UNREFERENCED_PARAMETER( hInstance );
	UNREFERENCED_PARAMETER( nCmdShow );
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );
		
	DDApplication* app = DDApplication::GetInstance();
	
	app->Init( L"Debris Defragmentation", 1000, 600 );

	PlayScene* scene = PlayScene::Create();
	scene->Init();

	// GameManager::GetInstance()->SetCurrentScene( scene );
// 	app->GetSceneDirector()->CreateScene( L"playScene" );
// 	app->GetSceneDirector()->ChangeScene( L"playScene");
	app->GetSceneDirector()->ChangeScene( scene );
	
	app->Run();
	app->Release();

	return 0;
}