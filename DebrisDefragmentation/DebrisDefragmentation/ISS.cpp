#include "ISS.h"

ISS::ISS()
{
}

ISS::ISS( std::wstring modelPath ) : DDModel( modelPath )
{
}

ISS::~ISS()
{
}

void ISS::UpdateItSelf( float dTime )
{
	UNREFERENCED_PARAMETER( dTime );
	// 데브리를 정지합니다.
}


