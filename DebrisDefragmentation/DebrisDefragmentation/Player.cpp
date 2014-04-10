#include "Player.h"
#include "DDPhysics.h"

Player::Player()
: m_IsAccelerating( false ), m_AccelerationStart( 0 )
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

void Player::RotateDicrection( float y, float x )
{
	// ������!
	// ȸ�� ���� ����ġ �ϵ� �ڵ� ���� �� ��
	// SetRotation( x / 500, y / 500, 0 );
	IncreaseRotationY( y / 10 );
	IncreaseRotationX( x / 10 );
}