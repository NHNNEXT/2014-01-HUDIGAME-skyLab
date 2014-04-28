#include "stdafx.h"
#include "Actor.h"

BaseObject::BaseObject()
{
	D3DXMatrixIdentity( &m_Matrix );
	m_CollisionBox.m_Transform = &m_Matrix;
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

D3DXVECTOR3 BaseObject::GetViewDirection(float x, float y, float z)
{
	D3DXQUATERNION	qRotation;
	D3DXMATRIXA16 tempMatrix;

	D3DXMatrixIdentity( &tempMatrix );

	// rotation에서 쿼터니언 생성, yaw ptich roll 은 y, x, z 순서임
	D3DXQuaternionRotationYawPitchRoll( &qRotation, D3DXToRadian( y ), D3DXToRadian( x ), D3DXToRadian( z ) );

	// matrix를 affine변환이 적용된 형태로 변환 - 생략 가능?
	D3DXMatrixTransformation( &tempMatrix, NULL, NULL, &m_Scale, NULL, &qRotation, &m_Position );

	return D3DXVECTOR3( tempMatrix._31, tempMatrix._32, tempMatrix._33 );
}

CollisionBox BaseObject::GetCollisionBox() const
{
	// 지금 현재 기준으로 변환 행렬을 적용한 바운딩 박스를 리턴
	CollisionBox transformedBox;

	D3DXVECTOR4 tempMat;

	// 현재 위치
	D3DXVec3Transform( &tempMat, &m_CollisionBox.m_CenterPos, m_CollisionBox.m_Transform );
	transformedBox.m_CenterPos = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

	// 각 점 좌표
	D3DXVec3TransformCoordArray(
		transformedBox.m_PointList.data(), sizeof( D3DXVECTOR3 ),
		m_CollisionBox.m_PointList.data(), sizeof( D3DXVECTOR3 ),
		m_CollisionBox.m_Transform, BOX_POINT_COUNT
		);

	// 축
	for ( int i = 0; i < 3; ++i )
	{
		// 마지막 항을 0으로 해야 평행이동 값이 벡터에 반영되지 않음
		D3DXVECTOR4 tempAxis = D3DXVECTOR4( m_CollisionBox.m_AxisDir[i].x, m_CollisionBox.m_AxisDir[i].y, m_CollisionBox.m_AxisDir[i].z, 0 );

		D3DXVec4Transform( &tempMat, &tempAxis, m_CollisionBox.m_Transform );
		transformedBox.m_AxisDir[i] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

		transformedBox.m_AxisLen[i] = m_CollisionBox.m_AxisLen[i];
	}

	transformedBox.m_Radius = m_CollisionBox.m_Radius;
	transformedBox.m_Transform = m_CollisionBox.m_Transform;

	return transformedBox;
}