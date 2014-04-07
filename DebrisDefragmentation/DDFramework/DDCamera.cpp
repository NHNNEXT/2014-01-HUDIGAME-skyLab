#include "stdafx.h"
#include "DDCamera.h"
#include "DDRenderer.h"


DDCamera::DDCamera():
m_LookatPoint(0.0f, 0.0f, 10.0f)
{	
	SetPosition( 0.0f, 0.0f, 0.0f );
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
	D3DXQUATERNION	qRotation;

	m_Matrix = m_pParent->GetMatrix();

	D3DXVECTOR4 tempEye;
	D3DXVec3Transform( &tempEye, &m_Position, &m_Matrix );
	D3DXVECTOR3 vEyePt( D3DXVECTOR3( tempEye.x, tempEye.y, tempEye.z ) );

	D3DXVECTOR4 tempLock;
	D3DXVec3Transform( &tempLock, &m_LookatPoint, &m_Matrix );
	D3DXVECTOR3 vLookatPt( D3DXVECTOR3( tempLock.x, tempLock.y, tempLock.z ) );

	D3DXVECTOR4 tempUp;
	D3DXVec3Transform( &tempUp, &D3DXVECTOR3(0, 1, 0), &m_Matrix );
	D3DXVECTOR3 vUpVec( D3DXVECTOR3( tempUp.x, tempUp.y, tempUp.z ) );

	//D3DXVECTOR3 vEyePt( 0, 0, -5 );
	//D3DXVECTOR3 vLookatPt(0, 0, 0 );
	//D3DXVECTOR3 vUpVec( 0, 1, 0 );
	
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
