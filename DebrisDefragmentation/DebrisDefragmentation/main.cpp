#include "main.h"
#include "DDFramework.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	// create the application instance
	DDApplication* app = DDApplication::GetInstance();
	
	app->Init( L"Debri Fragmentation", 1000, 600);

	app->Run();
	app->Release();

	return 0;
}