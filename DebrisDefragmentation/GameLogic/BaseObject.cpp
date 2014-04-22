#include "stdafx.h"
#include "Actor.h"

BaseObject::BaseObject()
{
}


BaseObject::~BaseObject()
{
}


void BaseObject::Update( float dTime )
{
	UpdateItSelf(dTime);
}

D3DXVECTOR3 BaseObject::GetViewDirection()
{
	D3DXQUATERNION	qRotation;
	D3DXMATRIXA16 tempMatrix;

	D3DXMatrixIdentity( &tempMatrix );

	// rotation에서 쿼터니언 생성, yaw ptich roll 은 y, x, z 순서임
	D3DXQuaternionRotationYawPitchRoll( &qRotation, D3DXToRadian( m_Rotation.y ), D3DXToRadian( m_Rotation.x ), D3DXToRadian( m_Rotation.z ) );

	// matrix를 affine변환이 적용된 형태로 변환 - 생략 가능?
	D3DXMatrixTransformation( &tempMatrix, NULL, NULL, &m_Scale, NULL, &qRotation, &m_Position );

	return D3DXVECTOR3( tempMatrix._31, tempMatrix._32, tempMatrix._33 );
}