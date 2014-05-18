#include "stdafx.h"
#include "Protector.h"
#include "ActorManager.h"
#include "ObjectTable.h"


Protector::Protector()
{
	m_ClassName = CharacterClass::PROTECTOR;
}


Protector::~Protector()
{
}

bool Protector::UseSkill( ClassSkill skill, int id, const D3DXVECTOR3& direction )
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
	case ClassSkill::WARNING:
		return SkillWarning( id, direction );
	case ClassSkill::SHARE_OXYGEN:
		return SkillShareOxygen( id, direction );
	case ClassSkill::EMP:
		return SkillEMP( id, direction );
	default:
		break;
	}

	return false;
}

bool Protector::SkillWarning( int id, const D3DXVECTOR3& direction )
{
	return false;
}

bool Protector::SkillShareOxygen( int id, const D3DXVECTOR3& direction )
{
	// 쿨탐 체크
	if ( m_GlobalCooldown > 0.0f || m_CooldownTable[static_cast<int>( ClassSkill::SHARE_OXYGEN )] > 0.0f )
		return false;

	int targetId = NOTHING;
	D3DXVECTOR3 spinAxis; // 사용은 안 함

	// 나눠 줄 연료가 없다ㅠ
	if ( m_Oxygen < DEFAULT_OXYGEN_SHARE_AMOUNT )
		return false;

	std::tie( targetId, spinAxis ) = GObjectTable->GetActorManager()->DetectTarget( id, direction );

	// 타겟이 없으면 그냥 무시
	if ( targetId == NOTHING )
		return false;

	if ( GObjectTable->GetInstance<Character>( targetId )->GetTeam()
		!= GObjectTable->GetInstance<Character>( id )->GetTeam() )
		return false;

	m_Oxygen -= DEFAULT_OXYGEN_SHARE_AMOUNT;
	GObjectTable->GetInstance<ClassComponent>( targetId )->IncreaseOxygen( DEFAULT_OXYGEN_SHARE_AMOUNT );

	GObjectTable->GetActorManager()->BroadcastSkillResult( targetId, ClassSkill::SHARE_OXYGEN );

	// 스킬 썼으면 쿨 적용시키자
	SetCooldown( ClassSkill::SHARE_OXYGEN );

	return true;
}

bool Protector::SkillEMP( int id, const D3DXVECTOR3& direction )
{
	// 쿨탐 체크
	if ( m_GlobalCooldown > 0.0f || m_CooldownTable[static_cast<int>( ClassSkill::EMP )] > 0.0f )
		return false;

	// 돌면서 거리 안에 오는 애들은 다 EMP 효과 적용
	std::vector<int> targets = GObjectTable->GetActorManager()->DetectTargetsInRange( id, SKILL_RANGE );

	std::for_each( targets.begin(), targets.end(), [&]( const int& each )
	{
		// 상대편에만 적용
		if ( GObjectTable->GetInstance<ClassComponent>( each )->GetTeam() != GObjectTable->GetInstance<ClassComponent>( id )->GetTeam() )
		{
			// EMP 쿨다운 적용하고 방송도 해버리자
			GObjectTable->GetInstance<ClassComponent>( each )->SetGlobalCooldown( EMP_TIME );
			GObjectTable->GetActorManager()->BroadcastSkillResult( each, ClassSkill::EMP );
		}
	}
	);

	// 스킬 썼으면 쿨 적용시키자
	SetCooldown( ClassSkill::EMP );

	return true;
}

void Protector::DoPeriodWork( float dTime )
{
	// 스킬이나 캐릭터 상태 변화 필요한 부분 ㄱㄱ
	UNREFERENCED_PARAMETER( dTime );
}