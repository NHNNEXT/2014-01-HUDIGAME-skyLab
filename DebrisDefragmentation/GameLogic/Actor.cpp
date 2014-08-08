#include "stdafx.h"
#include "Actor.h"
#include "Engineer.h"

#include "Physics.h"
#include "GameOption.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::UpdateItSelf( float dTime ) 
{ 
	// 가속
	if ( IsAccelerating() )
	{
		if ( timeGetTime() - GetAccelerationStartTime() > ACCELERATION_TIME )
		{
			// 가속 끝났다
			SetIsAccelerating( false );
			SetAcceleration( ZERO_VECTOR3 );
		}
	}
}

void Actor::IncreaseVelocity( const D3DXVECTOR3 &deltaVelocity )
{
	SetVelocity( GetVelocity() + deltaVelocity );
}

void Actor::Move( const D3DXVECTOR3& direction )
{ 
	// 가속 시작 시점 기록 - 타임 스탬프로 문제 해결
	// 나중에는 타이머 만들어서 써볼까?
	m_AccelerationStartTime = timeGetTime();
	SetIsAccelerating( true );

	D3DXVECTOR3 normalVec( 0, 0, 0 );
	D3DXVec3Normalize( &normalVec, &direction );

	m_Rigidbody.m_Acceleration += ( normalVec * ACCELERATION_WEIGHT );
}
/*
void Actor::AddForce( const D3DXVECTOR3 &direction )
{
SetAccelerationStartTime( timeGetTime( ) );
SetIsAccelerating( true );

D3DXVECTOR3 normalVec( ZERO_VECTOR3 );
D3DXVec3Normalize( &normalVec, &direction );

m_Rigidbody.m_Acceleration += ( normalVec * PUSHPULL_WEIGHT );
}
*/

void Actor::Stop() 
{ 
	// 장비를 정지합니다. 어 안되잖아? 어? 저, 정지가 안 돼, 정지시킬 수가 없어. 안-돼!
	m_Rigidbody.m_Acceleration = ZERO_VECTOR3;
	m_Rigidbody.m_Velocity = ZERO_VECTOR3;
}

void Actor::SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity )
{
	m_Rigidbody.m_SpinAngularVelocity = angularVelocity;
	m_Rigidbody.m_SpinAxis = rotationAxis;
	SetSpinTime( 0.0f );
	SetSpinnigFlag( true );
}

void Actor::AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity )
{
	// 조심해!!
	// 구현 중
}

void Actor::StopSpin()
{
	SetSpinnigFlag( false );
	SetSpinTime( 0.0f );
	m_Rigidbody.m_SpinAngularVelocity = 0.0f;
	m_Rigidbody.m_SpinAxis = ZERO_VECTOR3;
}

