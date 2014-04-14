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

void DDLight::RenderItSelf()
{
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof( D3DLIGHT9 ) );
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	// 조심해!
	// 방향 바꾸는 하드 코딩 나중에 삭제할 것
	vecDir = D3DXVECTOR3( cosf( timeGetTime() / 1000.0f ),
						  1.0f,
						  sinf( timeGetTime() / 1000.f ) );

	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
	light.Range = 10000.0f;
	m_pRenderer->GetDevice()->SetLight( 0, &light );
	m_pRenderer->GetDevice()->LightEnable( 0, TRUE );

	m_pRenderer->GetDevice()->SetRenderState( D3DRS_AMBIENT, 0x00888888 );

}
