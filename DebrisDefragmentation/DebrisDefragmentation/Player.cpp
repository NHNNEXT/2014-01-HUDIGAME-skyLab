#include "Player.h"
#include "DDPhysics.h"

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
	DDPhysics::CalcCurrentPosition( &m_Position, &m_Velocity, m_Acceleration, dTime );
}

void Player::SetAcceleration()
{
	DDVECTOR3 normalVec( 0, 0, 0 );
	DDVECTOR3 viewDirection( GetViewDirection() );
	DDPhysics::GetNormalVector( &viewDirection, &normalVec );

	// 조심해!
	// 가속도 가중치 하드 코딩 수정 할 것
	m_Acceleration += ( viewDirection * 0.1 );
}

void Player::Stop()
{
	// 장비를 정지합니다.
	m_Acceleration = DDVECTOR3( 0.0f, 0.0f, 0.0f );
	m_Velocity = DDVECTOR3( 0.0f, 0.0f, 0.0f );
}

void Player::RotateDicrection( float y, float x )
{
	// 조심해!
	// 회전 각도 가중치 하드 코딩 수정 할 것
	// SetRotation( x / 500, y / 500, 0 );
	IncreaseRotationY( y / 500 );
	IncreaseRotationX( x / 500 );
}