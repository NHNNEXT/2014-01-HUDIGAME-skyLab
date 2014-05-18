#include "stdafx.h"
#include "Engineer.h"
#include "ActorManager.h"
#include "ObjectTable.h"

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
	case ClassSkill::SET_SENTRY_GUN:
		return SkillSentryGun( id, direction );
	case ClassSkill::SET_DESPENSER:
		return SkillDespenser( id, direction );
	default:
		break;
	}

	return false;
}

bool Engineer::SkillGather( int id, const D3DXVECTOR3& direction )
{
	return false;
}

bool Engineer::SkillSentryGun( int id, const D3DXVECTOR3& direction )
{
	return false;
}

bool Engineer::SkillDespenser( int id, const D3DXVECTOR3& direction )
{
	return false;
}

void Engineer::DoPeriodWork( float dTime )
{
	// 스킬이나 캐릭터 상태 변화 필요한 부분 ㄱㄱ
	UNREFERENCED_PARAMETER( dTime );
}