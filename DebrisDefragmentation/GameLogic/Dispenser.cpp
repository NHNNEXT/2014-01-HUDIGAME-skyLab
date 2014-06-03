#include "stdafx.h"
#include "Dispenser.h"
#include "ObjectTable.h"
#include "ActorManager.h"

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
		if ( m_Team != eachCharacter->GetTeam( ) ) continue;
		
		// 범위 및 현재 거리 계산
		D3DXVECTOR4 tempMat;
		D3DXVECTOR3 dispenserPosition = GetTransform()->GetPosition();	// ISS 좌표계 기준 좌표

		// 현재 위치
		D3DXVec3Transform( &tempMat, &dispenserPosition, &m_Matrix );
		dispenserPosition = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

		D3DXVECTOR3 tmpRealDist = eachCharacter->GetTransform()->GetPosition() - dispenserPosition;
		float distance = D3DXVec3Length( &tmpRealDist );

		// 범위안에 있으면 켜고
		if ( distance < DISPENSER_RANGE )
		{
			if ( eachCharacter->GetClassComponent()->GetDispenserEffectFlag() ) continue;

			m_Fuel -= dTime * DISPENSER_FUEL_EFFICIENCY;
			m_Oxygen -= dTime * DISPENSER_OXYGEN_EFFICIENCY;
			eachCharacter->GetClassComponent()->SetDispenserEffectFlag( true );			
			GObjectTable->GetActorManager()->BroadcastDispenserEffect( eachCharacter->GetCharacterId() , true);
		}
		// 범위안에 있지 않은데 flag가 켜있으면 끈다.
		// 만약 순회 순서 앞에 있는 디스펜서에서 플래그를 활성화 했는데
		// 다음 순회에서 거리가 멀다는 이유로 플래그를 비활성화 시키면???
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
