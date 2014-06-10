#include "stdafx.h"
#include "SolarWindEvent.h"
#include "Physics.h"
#include "ActorManager.h"
#include "ObjectTable.h"


SolarWindEvent::SolarWindEvent()
{
	m_Event = GameEvent::SOLAR_WIND;
}


SolarWindEvent::~SolarWindEvent()
{
}

void SolarWindEvent::Run()
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