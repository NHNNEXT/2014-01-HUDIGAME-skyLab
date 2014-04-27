#include "DDCamera.h"
#include "DDRenderer.h"


DDCamera::DDCamera():
m_LookatPoint(0.0f, 0.0f, 10.0f)
{	
	// SetPosition( 0.0f, 1.0f, -5.0f );
	SetPosition( 0.0f, 0.0f, 1.0f );
}


DDCamera::~DDCamera()
{
}
// 
// DDCamera* DDCamera::Create()
// {
// 	DDCamera* pInstance = new DDCamera();
// 	return pInstance;
// }

void DDCamera::RenderItSelf()
{
	D3DXMATRIXA16 parentMatrix = m_pParent->GetMatrix( );
	
	D3DXVECTOR4 tempEye;
	D3DXVec3Transform( &tempEye, &m_Position, &parentMatrix );
	DDVECTOR3 vEyePt( tempEye.x, tempEye.y, tempEye.z );

	D3DXVECTOR4 tempLook;
	D3DXVec3Transform( &tempLook, &m_LookatPoint, &parentMatrix );
	DDVECTOR3 vLookatPt( tempLook.x, tempLook.y, tempLook.z );

	DDVECTOR3 vUpVec( parentMatrix._21, parentMatrix._22, parentMatrix._23 );
	/*
	D3DXVECTOR4 tempEye;
	D3DXVec3Transform( &tempEye, &m_Position, &m_Matrix );
	DDVECTOR3 vEyePt( tempEye.x, tempEye.y, tempEye.z );

	D3DXVECTOR4 tempLook;
	D3DXVec3Transform( &tempLook, &m_LookatPoint, &m_Matrix );
	DDVECTOR3 vLookatPt( tempLook.x, tempLook.y, tempLook.z );

	DDVECTOR3 vUpVec( m_Matrix._21, m_Matrix._22, m_Matrix._23 );
	*/

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_VIEW, &matView );

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );
	DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_PROJECTION, &matProj );
}

