#include "main.h"
#include "DDApplication.h"
#include "DDSceneDirector.h"
#include "DDScene.h"
#include "DDModel.h"
#include "DDCamera.h"
#include "DDLight.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	DDApplication* app = DDApplication::GetInstance();
	app->Init( L"Debris Defragmentation", 1000, 600 );
	DDScene* scene = DDScene::Create();
	DDModel* model = DDModel::Create( L"tiger.x" );
	DDCamera* camera = DDCamera::Create();
	DDLight* light = DDLight::Create();

	scene->AddChild( light );
	scene->AddChild( model );
	scene->AddChild( camera );
	DDSceneDirector::GetInstance()->ChangeScene( scene );

	

	app->Run();
	app->Release();

	return 0;
}