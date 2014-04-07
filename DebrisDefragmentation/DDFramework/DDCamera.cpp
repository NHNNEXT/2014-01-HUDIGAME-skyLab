#include "stdafx.h"
#include "DDCamera.h"
#include "DDRenderer.h"


DDCamera::DDCamera()
{
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
	// ���Ŀ� rotation�� �̿��ؼ� upvector
	// position���� eyePt, ��������, input�޾Ƽ� lookatPT�������ҵ�.
	D3DXVECTOR3 vEyePt( 0.0f, 3.0f, -10.0f );
	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_VIEW, &matView );

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );
	DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_PROJECTION, &matProj );

	DDObject::Render();
}

void DDCamera::Update( float dTime )
{
	DDObject::Update( dTime );
}
