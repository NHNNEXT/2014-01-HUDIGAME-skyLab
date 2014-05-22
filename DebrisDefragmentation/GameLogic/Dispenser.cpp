#include "stdafx.h"
#include "Dispenser.h"
#include "ObjectTable.h"
#include "ActorManager.h"


Dispenser::Dispenser()
{
}


Dispenser::~Dispenser()
{
}

void Dispenser::UpdateItSelf( float dTime )
{
	// 매 dt마다 충전
	m_Oxygen += dTime * DISPENSER_OXYGEN_INCREASE;
	m_Fuel += dTime * DISPENSER_FUEL_INCREASE;

	// 위치 이동, 계산 결과가 이상함 일단 보류
	//m_Transform.IncreasePositionZ( GObjectTable->GetActorManager()->GetIssPositionZ() );

	// 한 타임에 줄 수 있는 양보다 가진 양이 적으면 리턴
	if ( dTime * DISPENSER_OXYGEN_EFFICIENCY > m_Oxygen || dTime * DISPENSER_FUEL_EFFICIENCY > m_Fuel )
		return;

	// 근처에 있는 캐릭터 찾아서 나눠주기
	for ( const auto& eachCharacter : GObjectTable->GetActorManager()->GetCharacterList() )
	{
		// 캐릭터 리스트가 비어있으면 통과
		if ( eachCharacter == nullptr ) continue;

		// 다른 팀이어도 통과
		if ( m_TeamColor != eachCharacter->GetTeam() ) continue;
		
		// 범위 및 현재 거리 계산
		float range = eachCharacter->GetCollisionBox()->m_Radius + DISPENSER_RANGE;
		D3DXVECTOR3 tmpRealDist = eachCharacter->GetTransform()->GetPosition() - GetTransform()->GetPosition();
		float dist = sqrt( pow( tmpRealDist.x, 2 ) + pow( tmpRealDist.y, 2 ) + pow( tmpRealDist.z, 2 ) );

		// 범위안에 있으면 켜고
		if ( dist < range )
		{
			if ( eachCharacter->GetClassComponent()->GetDispenserEffectFlag() ) continue;

			m_Fuel -= dTime * DISPENSER_FUEL_EFFICIENCY;
			m_Oxygen -= dTime * DISPENSER_OXYGEN_EFFICIENCY;
			eachCharacter->GetClassComponent()->SetDispenserEffectFlag( true );			
			GObjectTable->GetActorManager()->BroadcastDispenserEffect( eachCharacter->GetCharacterId() , true);
		}
		// 범위안에 있지 않은데 flag가 켜있으면 끈다.
		else
		{
			if ( eachCharacter->GetClassComponent()->GetDispenserEffectFlag() )
			{
				eachCharacter->GetClassComponent()->SetDispenserEffectFlag( false );
				GObjectTable->GetActorManager()->BroadcastDispenserEffect( eachCharacter->GetCharacterId(), false );
			}
		}
	}
}
