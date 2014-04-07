#include "Player.h"


Player::Player()
{
	m_Camera = DDCamera::Create();
	m_Character = Character::Create(L"tiger.x");

	AddChild( m_Camera );
	AddChild( m_Character );
}


Player::~Player()
{
}

void Player::Render()
{
	DDObject::Render();
}

void Player::Update( float dTime )
{
	DDObject::Update( dTime );
}
