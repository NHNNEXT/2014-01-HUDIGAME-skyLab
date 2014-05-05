#include "ObjectISS.h"

ObjectISS::ObjectISS()
{
}

ObjectISS::ObjectISS( std::wstring modelPath ) : DDModel( modelPath )
{
}

ObjectISS::~ObjectISS()
{
}

void ObjectISS::UpdateItSelf( float dTime )
{
	UNREFERENCED_PARAMETER( dTime );
	// 데브리를 정지합니다.
}


