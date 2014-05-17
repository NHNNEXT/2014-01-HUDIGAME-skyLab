#include "stdafx.h"
#include "Striker.h"
#include "Character.h"
#include "ActorManager.h"
#include "ObjectTable.h"

Striker::Striker()
{
	m_ClassName = CharacterClass::STRIKER;
}


Striker::~Striker()
{
}

bool Striker::UseSkill( ClassSkill skill, int id, const D3DXVECTOR3& direction )
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
	case ClassSkill::PULL:
		return SkillPull( id, direction );
	case ClassSkill::SET_MINE:
		return SkillSetMine( id, direction );
	case ClassSkill::MOVE_FAST:
		return SkillMoveFast( id, direction );
	default:
		break;
	}

	return false;
}

bool Striker::SkillPull( int id, const D3DXVECTOR3& direction )
{
	// 쿨탐 체크
	if ( m_GlobalCooldown > 0.0f || m_CooldownTable[static_cast<int>( ClassSkill::PULL )] > 0.0f )
		return false;

	int targetId = NOTHING;
	D3DXVECTOR3 spinAxis;

	// 타겟을 검출한다.
	std::tie( targetId, spinAxis ) = GObjectTable->GetActorManager()->DetectTarget( id, direction );

	if ( targetId == NOTHING )
		return false;

	// 타겟이 있으므로 스킬 결과를 반영한다.
	Character* targetCharacter = GObjectTable->GetInstance<Character>( targetId );
	D3DXVECTOR3 force = targetCharacter->GetTransform()->GetPosition() - GObjectTable->GetInstance<Transform>( id )->GetPosition();

	// 변화 적용
	targetCharacter->GetClassComponent()->AddForce( -force );
	targetCharacter->GetClassComponent()->SetSpin( spinAxis, DEFAULT_SPIN_ANGULAR_VELOCITY );

	GObjectTable->GetActorManager()->BroadcastSkillResult( targetId, ClassSkill::PULL );
	
	// 스킬 썼으면 쿨 적용시키자
	m_CooldownTable[static_cast<int>( ClassSkill::PULL )] = COOLDOWN_PULL;

	return true;
}

bool Striker::SkillSetMine( int id, const D3DXVECTOR3& direction )
{
	return false;
}

bool Striker::SkillMoveFast( int id, const D3DXVECTOR3& direction )
{
	// 쿨탐 체크
	if ( m_GlobalCooldown > 0.0f || m_CooldownTable[static_cast<int>( ClassSkill::MOVE_FAST )] > 0.0f )
		return false;

	m_SpeedConstant = SCOUT_MOVE_FAST_CONSTANT;

	GObjectTable->GetActorManager()->BroadcastSkillResult( id, ClassSkill::MOVE_FAST );

	// 스킬 썼으면 쿨 적용시키자
	m_CooldownTable[static_cast<int>( ClassSkill::MOVE_FAST )] = COOLDOWN_MOVE_FAST;

	return true;
}