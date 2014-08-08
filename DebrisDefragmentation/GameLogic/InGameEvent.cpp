#include "stdafx.h"
#include "InGameEvent.h"
#include "ObjectTable.h"
#include "ActorManager.h"


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
	std::normal_distribution<float> fDist( 30.0f, 60.0f );
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
		if ( m_LifeTime == DS_LIFETIME )
		{
			// GObjectTable->GetActorManager()->BroadcastDisasterOccurrence( m_Direction, m_LifeTime );
		}

		m_LifeTime -= dt;
		if ( m_LifeTime < 0.0f )
		{
			// 이벤트 종료
			// 새 이벤트 생성하고 m_LifeTime 시간을 초기화
			m_LifeTime = DS_LIFETIME;

			// 그리고 리턴
			return true;
		}
		Run();
	}

	return false;
}