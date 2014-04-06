#include "main.h"
#include "DDApplication.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );
	
	DDApplication* app = DDApplication::GetInstance();
	app->Init( L"Debris Defragmentation", 1000, 600 );

	app->Run();
	app->Release();

	return 0;
}