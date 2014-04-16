#include "stdafx.h"
#include "Debris.h"
#include "DDRenderer.h"
#include "DDApplication.h"

Debris::Debris( )
{
}


Debris::Debris( wchar_t* modelPath ) : DDModel( modelPath )
{
}

Debris::~Debris( )
{
}

Debris* Debris::Create( wchar_t* modelPath )
{
	Debris* pInstance = new Debris( modelPath );
	return pInstance;
}

void Debris::UpdateItSelf( float dTime )
{
	UNREFERENCED_PARAMETER( dTime );
	// 데브리를 정지합니다.
}


