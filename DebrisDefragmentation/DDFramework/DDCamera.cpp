#include "stdafx.h"
#include "DDCamera.h"
#include "DDRenderer.h"


DDCamera::DDCamera():
m_LookatPoint(0.0f, 0.0f, 10.0f)
{	
	SetPosition( 0.0f, 3.0f, -10.0f );
}


DDCamera::~DDCamera()
{
}

DDCamera* DDCamera::Create()
{
	DDCamera* pInstance = new DDCamera();
	return pInstance;
}

void DDCamera::Render()
{
	DDObject::Render();
		
	// position으로 eyePt, 만들어야함, input받아서 lookatPT만들어야할듯.
	
// 	D3DXVECTOR3 vEyePt( 0.0f, 3.0f, -10.0f );
// 	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
// 	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );

	D3DXVECTOR3 vEyePt( m_Position );
	D3DXVECTOR3 vLookatPt( m_LookatPoint );
	D3DXVECTOR3 vUpVec( m_Matrix._21, m_Matrix._22, m_Matrix._23 );
	
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_VIEW, &matView );

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );
	DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_PROJECTION, &matProj );

}

void DDCamera::Update( float dTime )
{
	DDObject::Update( dTime );
}
