#include "stdafx.h"
#include "Actor.h"
#include "Physics.h"
#include "GameConfig.h"

Actor::Actor()
{
}


Actor::~Actor()
{
}

void Actor::SetAcceleration()
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
	m_RigidBody.m_Acceleration += ( viewDirection * ACCELERATION_WEIGHT );
}

void Actor::SetAccelerarion( const D3DXVECTOR3 &direction )
{
	m_AccelerationStart = timeGetTime();
	m_IsAccelerating = true;

	m_RigidBody.m_Acceleration += ( direction * ACCELERATION_WEIGHT );
}

void Actor::Stop()
{
	// 장비를 정지합니다. 어 안되잖아? 어? 저, 정지가 안 돼, 정지시킬 수가 없어. 안-돼!
	///# 앙대!
	m_RigidBody.m_Acceleration = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_RigidBody.m_Velocity = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
}
