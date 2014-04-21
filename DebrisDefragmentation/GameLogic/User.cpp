#include "stdafx.h"
#include "User.h"
#include "Physics.h"

User::~User()
{
}

void User::UpdateItSelf( float dTime )
{
	if ( m_IsAccelerating )
	{
		// 조심해! 
		// 하드코딩 로직 구현하면서 다 바꿀 것 
		if ( timeGetTime() - m_AccelerationStart > 500 )
		{
			// 가속 끝났다
			m_IsAccelerating = false;
			m_RigidBody.acceleration = D3DXVECTOR3( 0, 0, 0 );
		}
	}

	Physics::CalcCurrentPosition( &m_Position, &m_RigidBody.velocity, m_RigidBody.acceleration, dTime );
}

void User::RotateDicrection( float y, float x )
{
	// 조심해!
	// 하드코딩 - 로직 구현하면서 다 바꾸자?!
	SetRotation( x / 10, y / 10, 0 );
}