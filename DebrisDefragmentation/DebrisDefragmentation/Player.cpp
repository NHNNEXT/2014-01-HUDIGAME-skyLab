#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
	RemoveChild( m_Camera );
	RemoveChild( m_Character );
}

void Player::Init()
{
	m_Camera = DDCamera::Create();
	m_Character = Character::Create( L"tiger.x" );	
		
	AddChild( m_Camera );
	AddChild( m_Character );
}

void Player::Update( float dTime )
{
	UpdateItSelf( dTime );
	UpdateChildNodes( dTime );
}

void Player::UpdateItSelf( float dTime )
{

}
