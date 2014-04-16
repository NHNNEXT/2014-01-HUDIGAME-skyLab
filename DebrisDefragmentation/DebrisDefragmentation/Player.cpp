#include "stdafx.h"
#include "Player.h"
#include "DDPhysics.h"
#include "DDCamera.h"
#include "Character.h"
#include "NetworkManager.h"

Player::Player()
{
}

Player::Player( int playerId )
{
	m_PlayerId = playerId;
}


Player::~Player()
{
}

Player* Player::Create( int playerId )
{
	Player* pInstance = new Player( playerId );
	return pInstance;
}


void Player::Init()
{
	if ( GNetworkManager->GetMyPlayerId() == m_PlayerId )
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
		if ( timeGetTime() - m_AccelerationStart > 500 )
		{
			// 가속 끝났다
			m_IsAccelerating = false;
			m_Acceleration = DDVECTOR3( 0, 0, 0 );
		}
	}

	DDPhysics::CalcCurrentPosition( &m_Position, &m_Velocity, m_Acceleration, dTime );
}

void Player::SetAcceleration()
{
	// 가속 시작 시점 기록 - 타임 스탬프로 문제 해결
	// 나중에는 타이머 만들어서 써볼까?
	m_AccelerationStart = timeGetTime();
	m_IsAccelerating = true;

	DDVECTOR3 normalVec( 0, 0, 0 );
	DDVECTOR3 viewDirection( GetViewDirection() );
	DDPhysics::GetNormalVector( &viewDirection, &normalVec );

	// 조심해!
	// 가속도 가중치 하드 코딩 수정 할 것
	m_Acceleration += ( viewDirection * 1.0f );
}

void Player::Stop()
{
	// 장비를 정지합니다. 어 안되잖아? 어? 저, 정지가 안 돼, 정지시킬 수가 없어. 안-돼!
	m_Acceleration = DDVECTOR3( 0.0f, 0.0f, 0.0f );
	m_Velocity = DDVECTOR3( 0.0f, 0.0f, 0.0f );
}

void Player::RotateDicrection( double x, double y )
{
	// 조심해!
	// 회전 각도 가중치 하드 코딩 수정 할 것
	// SetRotation( x / 500, y / 500, 0 );
	IncreaseRotationX( x / 10 );
	IncreaseRotationY( y / 10 );
	
}