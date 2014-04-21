#include "stdafx.h"
#include "Debris.h"
#include "DDRenderer.h"
#include "DDApplication.h"

Debris::Debris( )
{
}


Debris::Debris( std::wstring modelPath ) : DDModel( modelPath )
{
}

Debris::~Debris( )
{
}

void Debris::UpdateItSelf( float dTime )
{
	UNREFERENCED_PARAMETER( dTime );
	// 데브리를 정지합니다.
}


