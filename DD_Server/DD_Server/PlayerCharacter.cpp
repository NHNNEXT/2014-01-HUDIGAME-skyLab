#include "stdafx.h"
#include "PlayerCharacter.h"
#include "Physics.h"

PlayerCharacter::PlayerCharacter() :
m_Position( .0f, .0f, .0f ), 
m_Rotation( .0f, .0f, .0f ),
m_Scale( 1.0f, 1.0f, 1.0f ),
m_Acceleration( .0f, .0f, .0f ),
m_Velocity( .0f, .0f, .0f ),
m_IsAccelerating( false ),
m_AccelerationStart( 0 )
{
}


PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::update( float dTime )
{
	if ( m_IsAccelerating )
	{
		if ( timeGetTime() - m_AccelerationStart > 500 )
		{
			// ���� ������
			m_IsAccelerating = false;
			m_Acceleration = DDVECTOR3( 0, 0, 0 );
		}
	}

	Physics::CalcCurrentPosition( &m_Position, &m_Velocity, m_Acceleration, dTime );
}

DDVECTOR3 PlayerCharacter::GetViewDirection()
{
	D3DXQUATERNION	qRotation;
	D3DXMATRIXA16 tempMatrix;

	D3DXMatrixIdentity( &tempMatrix );

	// rotation���� ���ʹϾ� ����, yaw ptich roll �� y, x, z ������
	D3DXQuaternionRotationYawPitchRoll( &qRotation, D3DXToRadian( m_Rotation.y ), D3DXToRadian( m_Rotation.x ), D3DXToRadian( m_Rotation.z ) );

	// matrix�� affine��ȯ�� ����� ���·� ��ȯ - ���� ����?
	D3DXMatrixTransformation( &tempMatrix, NULL, NULL, &m_Scale, NULL, &qRotation, &m_Position );

	return D3DXVECTOR3( tempMatrix._31, tempMatrix._32, tempMatrix._33 );
}

void PlayerCharacter::SetAcceleration()
{
	// ���� ���� ���� ��� - Ÿ�� �������� ���� �ذ�
	// ���߿��� Ÿ�̸� ���� �Ẽ��?
	m_AccelerationStart = timeGetTime();
	m_IsAccelerating = true;

	DDVECTOR3 normalVec( 0, 0, 0 );
	DDVECTOR3 viewDirection( GetViewDirection() );
	Physics::GetNormalVector( &viewDirection, &normalVec );

	// ������!
	// ���ӵ� ����ġ �ϵ� �ڵ� ���� �� ��
	m_Acceleration += ( viewDirection * 1.0f );
}

void PlayerCharacter::Stop()
{
	// ��� �����մϴ�. �� �ȵ��ݾ�? ��? ��, ������ �� ��, ������ų ���� ����. ��-��!
	m_Acceleration = DDVECTOR3( 0.0f, 0.0f, 0.0f );
	m_Velocity = DDVECTOR3( 0.0f, 0.0f, 0.0f );
}

void PlayerCharacter::RotateDicrection( float y, float x )
{
	SetRotation( x / 10, y / 10, 0 );
}