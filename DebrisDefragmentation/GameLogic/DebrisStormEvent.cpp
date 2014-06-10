#include "stdafx.h"
#include "DebrisStormEvent.h"
#include "Physics.h"
#include "ActorManager.h"
#include "ObjectTable.h"

DebrisStormEvent::DebrisStormEvent()
{
	m_Event = GameEvent::DEBRIS_STORM;
}


DebrisStormEvent::~DebrisStormEvent()
{
}

void DebrisStormEvent::Run()
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