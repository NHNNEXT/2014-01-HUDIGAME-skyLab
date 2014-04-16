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
			// ���� ������
			m_IsAccelerating = false;
			m_Acceleration = DDVECTOR3( 0, 0, 0 );
		}
	}

	DDPhysics::CalcCurrentPosition( &m_Position, &m_Velocity, m_Acceleration, dTime );
}

void Player::SetAcceleration()
{
	// ���� ���� ���� ��� - Ÿ�� �������� ���� �ذ�
	// ���߿��� Ÿ�̸� ���� �Ẽ��?
	m_AccelerationStart = timeGetTime();
	m_IsAccelerating = true;

	DDVECTOR3 normalVec( 0, 0, 0 );
	DDVECTOR3 viewDirection( GetViewDirection() );
	DDPhysics::GetNormalVector( &viewDirection, &normalVec );

	// ������!
	// ���ӵ� ����ġ �ϵ� �ڵ� ���� �� ��
	m_Acceleration += ( viewDirection * 1.0f );
}

void Player::Stop()
{
	// ��� �����մϴ�. �� �ȵ��ݾ�? ��? ��, ������ �� ��, ������ų ���� ����. ��-��!
	m_Acceleration = DDVECTOR3( 0.0f, 0.0f, 0.0f );
	m_Velocity = DDVECTOR3( 0.0f, 0.0f, 0.0f );
}

void Player::RotateDicrection( double x, double y )
{
	// ������!
	// ȸ�� ���� ����ġ �ϵ� �ڵ� ���� �� ��
	// SetRotation( x / 500, y / 500, 0 );
	IncreaseRotationX( x / 10 );
	IncreaseRotationY( y / 10 );
	
}