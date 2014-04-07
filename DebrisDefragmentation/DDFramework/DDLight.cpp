#include "stdafx.h"
#include "DDLight.h"
#include "DDRenderer.h"


DDLight::DDLight()
{
}


DDLight::~DDLight()
{
}

DDLight* DDLight::Create()
{
	DDLight* pInstance = new DDLight();
	return pInstance;
}

void DDLight::Render()
{
	DDObject::Render();

	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof( D3DLIGHT9 ) );
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	vecDir = D3DXVECTOR3( cosf( timeGetTime() / 350.0f ),
						  1.0f,
						  sinf( timeGetTime() / 350.f ) );

	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
	light.Range = 1000.0f;
	DDRenderer::GetInstance()->GetDevice()->SetLight( 0, &light );
	DDRenderer::GetInstance()->GetDevice()->LightEnable( 0, TRUE );

	DDRenderer::GetInstance()->GetDevice()->SetRenderState( D3DRS_AMBIENT, 0x00202020 );

}

void DDLight::Update( float dTime )
{
	DDObject::Update(dTime);
}
