#include "stdafx.h"
#include "Event.h"


Event::Event()
{
}


Event::~Event()
{
}

void Event::Init()
{
	// 시간을 초기화 한다.
	std::default_random_engine e;
	std::normal_distribution<float> fDist(180.0f, 360.0f);
	std::function<float()> rnd = std::bind( fDist, e );
	m_Timer = rnd();

	// 다음 이벤트의 종류를 설정한다.
	m_Event = ( rand() % 2 == 0 ) ? GameEvent::DEBRIS_STORM : GameEvent::SOLAR_WIND;
}

void Event::Run()
{
	// 적합한 이벤트 호출
	switch ( m_Event )
	{
	case GameEvent::DEBRIS_STORM:
		DebrisStorm();
		break;
	case GameEvent::SOLAR_WIND:
		SolarWind();
		break;
	default:
		break;
	}

	// 새로 다음 실행될 이벤트를 설정한다.
	Init();
}

// 실제 이벤트들 - 캐릭터들에 영향을 준다.
void Event::DebrisStorm()
{
	// 플레이어들에게 영향을 준다.
	printf_s( "Debris storm\n" );
}

void Event::SolarWind()
{
	// 플레이어들에게 영향을 준다.
	printf_s( "Solar wind\n" );
}

void Event::Update( float dt )
{
	m_Timer -= dt;
	if ( m_Timer <= 0.0f )
	{
		m_Timer = 0.0f;
		Run();
	}
}