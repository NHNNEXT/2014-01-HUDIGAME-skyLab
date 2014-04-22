#include "stdafx.h"
#include "Character.h"
#include "Physics.h"

Character::~Character()
{
}

void Character::UpdateItSelf( float dTime )
{
	if ( m_IsAccelerating )
	{
		// 조심해! 
		// 하드코딩 로직 구현하면서 다 바꿀 것 
		if ( timeGetTime( ) - m_AccelerationStart > ACCELERATION_TIME )
		{
			// 가속 끝났다
			m_IsAccelerating = false;
			m_RigidBody.m_Acceleration = D3DXVECTOR3( 0, 0, 0 );
		}
	}

	Physics::CalcCurrentPosition( &m_Position, &m_RigidBody.m_Velocity, m_RigidBody.m_Acceleration, dTime );
}