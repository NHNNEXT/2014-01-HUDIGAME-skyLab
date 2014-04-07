#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	m_Camera = DDCamera::Create();
	m_Character = Character::Create( L"tiger.x" );	
	
	AddChild( m_Camera );
	AddChild( m_Character );
}