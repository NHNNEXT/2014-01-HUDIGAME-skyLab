#include "stdafx.h"
#include "Engineer.h"
#include "ActorManager.h"
#include "ObjectTable.h"
#include "Physics.h"

Engineer::Engineer()
{
	m_ClassName = CharacterClass::ENGINEER;
}


Engineer::~Engineer()
{
}

bool Engineer::UseSkill( ClassSkill skill, int id, const D3DXVECTOR3& direction )
{
	switch ( skill )
	{
	case ClassSkill::PUSH:
		return SkillPush( id, direction );
	case ClassSkill::OCCUPY:
		return SkillOccupy( id, direction );
	case ClassSkill::DESTROY:
		return SkillDestroy( id, direction );
	case ClassSkill::SHARE_FUEL:
		return SkillShareFuel( id, direction );
	case ClassSkill::GATHER:
		return SkillGather( id, direction );
	case ClassSkill::SET_SHELTER:
		return SkillShelter( id, direction );
	case ClassSkill::SET_DISPENSER:
		return SkillDispenser( id, direction );
	default:
		break;
	}

	return false;
}

bool Engineer::SkillGather( int id, const D3DXVECTOR3& direction )
{
	if ( m_GlobalCooldown > 0.0f || m_CooldownTable[static_cast<int>(ClassSkill::GATHER)] > 0.0f )
		return false;

	Character* character = GObjectTable->GetActorManager()->GetCharacterList().at( id );
	D3DXVECTOR3 viewDirection = character->GetViewDirection( direction );
	D3DXVECTOR3	startPoint = character->GetTransform()->GetPosition();

	//bool returnVal = GObjectTable->GetActorManager()->BuildDispenser( id, direction );
	bool returnVal = DebrisInRay( viewDirection, startPoint );
	
	// 캐릭터 자원 증가
	character->GetClassComponent()->IncreaseResource( DEBRIS_TO_RESOURCE_AMOUNT );

	// 레이에 맞은 데브리 삭제
	GObjectTable->GetActorManager()->RemoveResourceDebris( GObjectTable->GetActorManager()->GetGatheredDebris() );	

	// 스킬 썼으면 쿨 적용시키자
	if ( returnVal )
		SetCooldown( ClassSkill::GATHER );

	// broadcast
	GObjectTable->GetActorManager()->BroadcastSkillResult( static_cast<int>(id), ClassSkill::GATHER );

	return returnVal;
}

bool Engineer::SkillShelter( int id, const D3DXVECTOR3& direction )
{
	return false;
}

bool Engineer::SkillDispenser( int id, const D3DXVECTOR3& direction )
{
	// 쿨탐 체크
	if ( m_GlobalCooldown > 0.0f || m_CooldownTable[static_cast<int>( ClassSkill::SET_DISPENSER )] > 0.0f )
		return false;

	bool returnVal = GObjectTable->GetActorManager()->BuildDispenser( id, direction );

	// 스킬 썼으면 쿨 적용시키자
	if ( returnVal )
		SetCooldown( ClassSkill::SET_DISPENSER );

	return returnVal;	
}

void Engineer::DoPeriodWork( float dTime )
{
	// 스킬이나 캐릭터 상태 변화 필요한 부분 ㄱㄱ
	UNREFERENCED_PARAMETER( dTime );
}

bool Engineer::DebrisInRay( const D3DXVECTOR3 &viewDirection, const D3DXVECTOR3 &startPoint )
{
	float currentDistance = std::numeric_limits<float>::infinity();	
	int	debrisNumber = -1;

	auto& debrisList = GObjectTable->GetActorManager()->GetResourceDebrisList();
	for ( int i = 0; i < RESOURCE_DEBRIS_NUMBER; ++i )	
	{
		if ( debrisList[i] == nullptr ) continue;

		// intersection 확인
		float tempDistance = std::numeric_limits<float>::infinity();
		if ( Physics::IntersectionCheckRayBox( nullptr, &tempDistance, nullptr, viewDirection, startPoint, debrisList[i]->GetCollisionBox() ) )
		{			
			// 스킬 사용 범위가 정해지면 그것과 비교해서 더 먼 애는 제외
			// 더 가까운 애로 교체
			if ( tempDistance < currentDistance && tempDistance < SKILL_RANGE )
			{
				currentDistance = tempDistance;				
				debrisNumber = i;
			}
		}
	}

	GObjectTable->GetActorManager()->SetGatheredDebris( debrisNumber );
	return (debrisNumber == -1) ? false : true;

}
