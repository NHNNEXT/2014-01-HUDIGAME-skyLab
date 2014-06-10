#include "stdafx.h"
#include "InGameEvent.h"


InGameEvent::InGameEvent()
{
}


InGameEvent::~InGameEvent()
{
}

void InGameEvent::Init()
{
	// 시간을 초기화 한다.
	std::default_random_engine e;
	std::normal_distribution<float> fDist( 180.0f, 360.0f );
	std::function<float()> rnd = std::bind( fDist, e );
	m_Timer = rnd();

	// 이벤트 방향을 결정한다.
	m_Direction.x = static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX );
	m_Direction.y = static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX );
	m_Direction.z = static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX );
	D3DXVec3Normalize( &m_Direction, &m_Direction );
}

bool InGameEvent::Update( float dt )
{
	m_Timer -= dt;
	if ( m_Timer <= 0.0f )
	{
		m_Timer = 0.0f;
		Run();

		return true;
	}

	return false;
}