#include "main.h"
#include "DDApplication.h"
#include "DDSceneDirector.h"
#include "PlayScene.h"
#include "GameManager.h"
#include "Character.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( );

#endif 

	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	DDApplication* app = DDApplication::GetInstance();
	app->Init( L"Debris Defragmentation", 1000, 600 );

	PlayScene* scene = PlayScene::Create();
	scene->Init();

	// GameManager::GetInstance()->SetCurrentScene( scene );
	DDSceneDirector::GetInstance()->ChangeScene( scene );
	
	app->Run();
	app->Release();

	return 0;
}