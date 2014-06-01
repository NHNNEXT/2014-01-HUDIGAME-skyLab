#include "stdafx.h"
#include "DDCamera.h"
#include "DDRenderer.h"
#include "DDApplication.h"
#include "PlayerManager.h"
#include "NetworkManager.h"


DDCamera::DDCamera():
m_LookatPoint(0.0f, 0.0f, 10.0f)
{	
	GetTransform().SetPosition( 0.0f, 0.0f, 0.0f );
	SetAspectRatio();
}

DDCamera::~DDCamera()
{
}

void DDCamera::RenderItSelf()
{	
	if ( m_FirstPersonCamera && m_FollowingObject != nullptr )
	{
		//	D3DXMATRIXA16 m_Matrix;
		D3DXQUATERNION	qRotation;
		D3DXMatrixIdentity( &m_Matrix );

		// rotation에서 쿼터니언 생성, yaw ptich roll 은 y, x, z 순서임
		D3DXQuaternionRotationYawPitchRoll( &qRotation, D3DXToRadian( GetTransform().GetRotationY() ), D3DXToRadian( GetTransform().GetRotationX() ), D3DXToRadian( m_FollowingObject->GetTransform().GetRotationZ() ) );

		// matrix를 affine변환이 적용된 형태로 변환	
		D3DXVECTOR3 scale = GetTransform().GetScale();
		D3DXVECTOR3 fPos = m_FollowingObject->GetTransform().GetPosition();
		D3DXMatrixTransformation( &m_Matrix, NULL, NULL, &scale, NULL, &qRotation, &fPos );

		Player* player = GPlayerManager->GetPlayer( GNetworkManager->GetMyPlayerId() );
		if ( player->IsSpinning() )
		{
			// 플레이어와 카메라의 회전 동기화
			D3DXMATRIXA16 spinTransform;
			D3DXVECTOR3 tmpSpinAxis = player->GetSpinAxis();
			float tmpSpinAngle = player->GetSpinAngularVelocity();
			D3DXMatrixRotationAxis( &spinTransform, &tmpSpinAxis, tmpSpinAngle * player->GetSpinTime() );
			D3DXMatrixMultiply( &m_Matrix, &spinTransform, &m_Matrix );
		}
	}
	

	D3DXVECTOR4 tempEye;
	D3DXVECTOR3 pos = GetTransform().GetPosition();
	D3DXVec3Transform( &tempEye, &pos, &m_Matrix );
	D3DXVECTOR3 vEyePt = DDVECTOR3( tempEye.x, tempEye.y, tempEye.z );

	D3DXVECTOR4 tempLook;
	D3DXVec3Transform( &tempLook, &m_LookatPoint, &m_Matrix );
	D3DXVECTOR3 vLookatPt = DDVECTOR3( tempLook.x, tempLook.y, tempLook.z );

	D3DXVECTOR3 vUpVec = DDVECTOR3( m_Matrix._21, m_Matrix._22, m_Matrix._23 );


	
	D3DXMatrixLookAtLH( &m_MatView, &vEyePt, &vLookatPt, &vUpVec );
	DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_VIEW, &m_MatView );

	
	// 주의 : 반드시 SetAspectRatio() 먼저 해둘 것
	float aspectRatio = WindowsWidth / WindowsHeight;
	D3DXMatrixPerspectiveFovLH( &m_MatProj, D3DX_PI / 5, aspectRatio, 0.5f, 2000.0f );
	DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_PROJECTION, &m_MatProj );
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