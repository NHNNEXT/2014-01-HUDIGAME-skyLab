#include "stdafx.h"
#include "Transform.h"


Transform::Transform()
{
}


Transform::~Transform()
{
}

D3DXMATRIXA16 Transform::MatrixTransform()
{
	D3DXQUATERNION	qRotation;
	D3DXMATRIXA16	tempMatrix;

	D3DXMatrixIdentity( &tempMatrix );

	// rotation���� ���ʹϾ� ����, yaw ptich roll �� y, x, z ������
	D3DXQuaternionRotationYawPitchRoll( &qRotation, D3DXToRadian( m_Rotation.y ), D3DXToRadian( m_Rotation.x ), D3DXToRadian( m_Rotation.z ) );

	// matrix�� affine��ȯ�� ����� ���·� ��ȯ	
	D3DXMatrixTransformation( &tempMatrix, NULL, NULL, &m_Scale, NULL, &qRotation, &m_Position );

	return tempMatrix;
}
