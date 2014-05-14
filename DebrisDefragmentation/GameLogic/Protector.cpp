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

	return true;
}

bool Protector::SkillEMP( int id, const D3DXVECTOR3& direction )
{
	return false;
}