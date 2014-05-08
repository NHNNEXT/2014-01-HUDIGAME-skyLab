#include "stdafx.h"
#include "DDCamera.h"
#include "DDRenderer.h"
#include "DDApplication.h"


DDCamera::DDCamera():
m_LookatPoint(0.0f, 0.0f, 10.0f)
{	
	SetPosition( 0.0f, 0.0f, 0.0f );
	SetAspectRatio();
}

DDCamera::~DDCamera()
{
}

void DDCamera::RenderItSelf()
{
	DDVECTOR3 vEyePt, vLookatPt, vUpVec;
	if ( m_EmbeddedCamera || m_FollowingObject == nullptr )
	{
		D3DXVECTOR4 tempEye;
		D3DXVec3Transform( &tempEye, &m_Position, &m_Matrix );
		vEyePt = DDVECTOR3( tempEye.x, tempEye.y, tempEye.z );

		D3DXVECTOR4 tempLook;
		D3DXVec3Transform( &tempLook, &m_LookatPoint, &m_Matrix );
		vLookatPt = DDVECTOR3( tempLook.x, tempLook.y, tempLook.z );

		vUpVec = DDVECTOR3( m_Matrix._21, m_Matrix._22, m_Matrix._23 );
	}
	else 
	{
		D3DXMATRIXA16 tmpMatrix;
		D3DXQUATERNION	qRotation;
		D3DXMatrixIdentity( &tmpMatrix );

		// rotation에서 쿼터니언 생성, yaw ptich roll 은 y, x, z 순서임
		D3DXQuaternionRotationYawPitchRoll( &qRotation, D3DXToRadian( m_Rotation.y ), D3DXToRadian( m_Rotation.x ), D3DXToRadian( m_FollowingObject->GetRotationZ() ) );

		// matrix를 affine변환이 적용된 형태로 변환	
		D3DXMatrixTransformation( &tmpMatrix, NULL, NULL, &m_Scale, NULL, &qRotation, &m_FollowingObject->GetPosition() );

		D3DXVECTOR4 tempEye;
		D3DXVec3Transform( &tempEye, &m_Position, &tmpMatrix );
		vEyePt = DDVECTOR3( tempEye.x, tempEye.y, tempEye.z );

		D3DXVECTOR4 tempLook;
		D3DXVec3Transform( &tempLook, &m_LookatPoint, &tmpMatrix );
		vLookatPt = DDVECTOR3( tempLook.x, tempLook.y, tempLook.z );

		vUpVec = DDVECTOR3( tmpMatrix._21, tmpMatrix._22, tmpMatrix._23 );

	}
	
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_VIEW, &matView );

	D3DXMATRIXA16 matProj;
	// 주의 : 반드시 SetAspectRatio() 먼저 해둘 것
	float aspectRatio = WindowsWidth / WindowsHeight;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 5, aspectRatio, 1.0f, 2000.0f );
	DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_PROJECTION, &matProj );
}

// default
void DDCamera::SetAspectRatio()
{
	SetAspectRatio( static_cast<float>( DDApplication::GetInstance()->GetScreenWidth() ),
		static_cast<float>( DDApplication::GetInstance()->GetScreenHeight() ) );
}

// wrapper 에서 쓸려고 만들었음
void DDCamera::SetAspectRatio( float width, float height )
{
	WindowsWidth = width;
	WindowsHeight = height;
}