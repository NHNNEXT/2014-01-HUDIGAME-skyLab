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
	// 조심해!!
	// 나중에 인자 입력받아서 클래스 종류별로 m_avatar에 지정해줄 것
	m_Avatar = ClassComponent::Create();
	m_Avatar->SetAvatarId( playerId );
}


Player::~Player()
{
}

void Player::Init()
{
	if ( GNetworkManager->GetMyPlayerId() == m_Avatar->GetAvatarId() )
	{
		m_Camera = DDCamera::Create();
		AddChild( m_Camera );
	}
	
	m_Character = Character::Create( L"tiger.x" );	
	AddChild( m_Character );
}

void Player::UpdateItSelf( float dTime )
{
	if ( m_Avatar->IsAccelerating() )
	{
		if ( timeGetTime() - m_Avatar->GetAccelerationStartTime() > 500 )
		{
			// 가속 끝났다
			m_Avatar->SetIsAccelerating( false );
			m_Rigidbody.acceleration = DDVECTOR3( 0, 0, 0 );
		}
	}

	Physics::CalcCurrentPosition( &m_Position, &m_Rigidbody.velocity, m_Rigidbody.acceleration, dTime );
}