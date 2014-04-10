#include "Debris.h"
#include "DDRenderer.h"

Debris::Debris( )
{
	tmpTimeCounter = 0;
}


Debris::Debris( wchar_t* modelPath )
{
	m_pD3DDevice = DDRenderer::GetInstance( )->GetDevice( );
	initModel( modelPath );
	SetNormalVector( );
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
	// 데브리를 정지합니다.
}


