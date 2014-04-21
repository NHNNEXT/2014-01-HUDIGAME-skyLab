#include "stdafx.h"
#include "Player.h"
#include "DDCamera.h"
#include "Character.h"
#include "NetworkManager.h"

#include "Physics.h"

Player::Player()
{
}

Player::Player( int playerId )
{
	m_AvatarId = playerId;
}


Player::~Player()
{
}

void Player::Init()
{
	if ( GNetworkManager->GetMyPlayerId() == m_AvatarId )
	{
		m_Camera = DDCamera::Create();
		AddChild( m_Camera );
	}
	
	m_Character = Character::Create( L"tiger.x" );	
	AddChild( m_Character );
}

void Player::UpdateItSelf( float dTime )
{
	if ( m_IsAccelerating )
	{
		if ( timeGetTime() - m_AccelerationStartTime > 500 )
		{
			// 가속 끝났다
			m_IsAccelerating = false;
			m_Rigidbody.acceleration = DDVECTOR3( 0, 0, 0 );
		}
	}

	Physics::CalcCurrentPosition( &m_Position, &m_Rigidbody.velocity, m_Rigidbody.acceleration, dTime );
}