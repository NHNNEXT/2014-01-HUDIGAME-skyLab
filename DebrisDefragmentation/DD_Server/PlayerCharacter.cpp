#include "stdafx.h"
#include "PlayerCharacter.h"
#include "Physics.h"

PlayerCharacter::PlayerCharacter( int playerId ) :
m_PlayerId( playerId ),
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

void PlayerCharacter::Update( float dTime )
{
	if ( m_IsAccelerating )
	{
		// 조심해! 
		// 하드코딩 로직 구현하면서 다 바꿀 것 
		if ( timeGetTime() - m_AccelerationStart > 500 )
		{
			// 가속 끝났다
			m_IsAccelerating = false;
			m_Acceleration = D3DXVECTOR3( 0, 0, 0 );
		}
	}

	Physics::CalcCurrentPosition( &m_Position, &m_Velocity, m_Acceleration, dTime );
}

D3DXVECTOR3 PlayerCharacter::GetViewDirection()
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

void PlayerCharacter::SetAcceleration()
{
	// 가속 시작 시점 기록 - 타임 스탬프로 문제 해결
	// 나중에는 타이머 만들어서 써볼까?
	m_AccelerationStart = timeGetTime();
	m_IsAccelerating = true;

	D3DXVECTOR3 normalVec( 0, 0, 0 );
	D3DXVECTOR3 viewDirection( GetViewDirection() );
	Physics::GetNormalVector( &viewDirection, &normalVec );

	// 조심해!
	// 가속도 가중치 하드 코딩 수정 할 것
	m_Acceleration += ( viewDirection * 1.0f );
}

void PlayerCharacter::Stop()
{
	// 장비를 정지합니다. 어 안되잖아? 어? 저, 정지가 안 돼, 정지시킬 수가 없어. 안-돼!
	///# 앙대!
	m_Acceleration = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_Velocity = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
}

void PlayerCharacter::RotateDicrection( float y, float x )
{
	// 조심해!
	// 하드코딩 - 로직 구현하면서 다 바꾸자?!
	SetRotation( x / 10, y / 10, 0 );
}