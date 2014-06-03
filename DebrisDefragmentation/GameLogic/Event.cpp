#include "stdafx.h"
#include "Event.h"
#include "Physics.h"
#include "ActorManager.h"
#include "ObjectTable.h"

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
	m_Timer = rnd(); ///# 이건 이벤트때마다 호출해주는건데.. 그 때마다 굳이 정규분포 엔진을 쓸 필요까지야... ㅎㅎㅎ

	// 다음 이벤트의 종류를 설정한다.
	m_Event = ( rand() % 2 == 0 ) ? GameEvent::DEBRIS_STORM : GameEvent::SOLAR_WIND;

	// 이벤트 방향을 결정한다.
	m_Direction.x = static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX );
	m_Direction.y = static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX );
	m_Direction.z = static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX );
	D3DXVec3Normalize( &m_Direction, &m_Direction );
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
	// 플레이어를 순회하면서 바운딩 박스의 모든 점이 가려지는지 확인
	// 안 가려지면 죽음으로 판정

	// iss에서 개별 모듈의 충돌박스를 받아야 되는데
	// iss는 ActorManager가 멤버로 들고 있으므로 요청할 수 밖에 없을 듯

	// ISS module 충돌박스 정보 갱신
	std::vector<const CollisionBox*> currentIssModuleBoundingBox;
	for ( int i = 0; i < MODULE_NUMBER; ++i )
	{
		currentIssModuleBoundingBox.push_back( GObjectTable->GetActorManager()->GetModuleBoundingBox( i ) );
	}

	// 가려지는지 확인
	for ( int i = 0; i < REAL_PLAYER_NUM; ++i )
	{
		Character* tempCharacter = GObjectTable->GetCharacter( i );

		if ( tempCharacter == nullptr )
			continue;

		if ( !Physics::IsCovered( tempCharacter->GetCollisionBox(), -m_Direction, currentIssModuleBoundingBox ) )
		{
			// 캐릭터에 이벤트 적용
			tempCharacter->GetClassComponent()->SetOxygen( 0.0f );

			// 조심해!!
			// 따로 함수 만들 것
			GObjectTable->GetActorManager()->BroadcastCharacterChange( i, ChangeType::CHARACTER_STATE );
		}
	}

	printf_s( "Debris storm\n" );
}

void Event::SolarWind()
{
	std::vector<const CollisionBox*> currentIssModuleBoundingBox;
	for ( int i = 0; i < MODULE_NUMBER; ++i )
	{
		currentIssModuleBoundingBox.push_back( GObjectTable->GetActorManager()->GetModuleBoundingBox( i ) );
	}

	// 가려지는지 확인
	for ( int i = 0; i < REAL_PLAYER_NUM; ++i )
	{
		Character* tempCharacter = GObjectTable->GetCharacter( i );

		if ( tempCharacter == nullptr )
			continue;

		if ( !Physics::IsCovered( tempCharacter->GetCollisionBox(), -m_Direction, currentIssModuleBoundingBox ) )
		{
			// 캐릭터에 이벤트 적용
			tempCharacter->GetClassComponent()->SetOxygen( 0.0f );

			// 조심해!!
			// 따로 함수 만들 것
			GObjectTable->GetActorManager()->BroadcastCharacterChange( i, ChangeType::CHARACTER_STATE );
		}
	}

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