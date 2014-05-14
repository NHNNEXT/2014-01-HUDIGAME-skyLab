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
	return false;
}

bool Protector::SkillEMP( int id, const D3DXVECTOR3& direction )
{
	return false;
}