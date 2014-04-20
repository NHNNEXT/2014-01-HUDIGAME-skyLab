#include "main.h"
#include "stdafx.h"
#include "DDApplication.h"
#include "PlayScene.h"
#include "GameManager.h"
#include "DDSceneDirector.h"
#include "GameLogic.h"
#include "NetworkManager.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 214 );

#endif 
	UNREFERENCED_PARAMETER( hInstance );
	UNREFERENCED_PARAMETER( nCmdShow );
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	DDApplication* app = DDApplication::GetInstance();
	GGameLogic = new GameLogic();

	app->Init( L"Debris Defragmentation", 1000, 600 );
	
	DDScene* scene = GGameLogic->CreateScene(L"PlayScene1");	
	
	DDSceneDirector::GetInstance()->ChangeScene( scene );

	app->Run();
	app->Release();

	//SafeDelete( scene );	

	delete GGameLogic;

	return 0;
}