#include "stdafx.h"
#include "Striker.h"
#include "Character.h"
#include "ActorManager.h"
#include "ObjectTable.h"
#include "Physics.h"

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
	targetCharacter->Move( -force );
	targetCharacter->SetSpin( spinAxis, DEFAULT_SPIN_ANGULAR_VELOCITY );

	GObjectTable->GetActorManager()->BroadcastSkillResult( targetId, ClassSkill::PULL );
	
	// 스킬 썼으면 쿨 적용시키자
	SetCooldown( ClassSkill::PULL );

	return true;
}

bool Striker::SkillSetMine( int id, const D3DXVECTOR3& direction )
{
	// 쿨탐 체크
	if ( m_GlobalCooldown > 0.0f || m_CooldownTable[static_cast<int>( ClassSkill::SET_MINE )] > 0.0f )
		return false;

	ISS* iss = GObjectTable->GetActorManager()->GetIss();

	D3DXVECTOR3 viewDirection = GObjectTable->GetInstance<Character>( id )->GetViewDirection( direction );
	D3DXVECTOR3	startPoint = GObjectTable->GetInstance<Transform>( id )->GetPosition();

	// 스킬 사용 방향에 있는 모듈 검색
	ISSModuleName targetModuleName = iss->ModuleOnRay( viewDirection, startPoint );
	
	if ( targetModuleName == ISSModuleName::NO_MODULE )
		return false;
	
	ISSModule* targetModule = GObjectTable->GetActorManager()->GetIss()->GetModule( targetModuleName );
	float distance = std::numeric_limits<float>::infinity();
	Physics::IntersectionCheckRayBox( nullptr, &distance, nullptr, viewDirection, startPoint, targetModule->GetCollisionBox() );

	// 모듈까지의 거리 체크 - 멀면 return false;
	if ( distance > SKILL_RANGE )
		return false;

	// 그렇지 않으면 바운딩 박스와 ray의 교점 위치에
	// ray 방향의 반대 방향을 정면으로 설정

	// 등록함수를 만들자

	// actorManager에 등록

	// 설치 완료

	return true;
}

bool Striker::SkillMoveFast( int id, const D3DXVECTOR3& direction )
{
	// 쿨탐 체크
	if ( m_GlobalCooldown > 0.0f || m_CooldownTable[static_cast<int>( ClassSkill::MOVE_FAST )] > 0.0f )
		return false;

	GObjectTable->GetInstance<Character>( id )->SetSpeedConstant( SCOUT_MOVE_FAST_CONSTANT );
	m_RemainFastMove = SCOUT_MOVE_FAST_DURATION;
	m_FastMoveTarget = id;

	// 일단 쿨탐과 같은 방식으로 진행하자
	// 스킬 쓰면 시간을 설정하고 dt만큼 감소 시키다가 0이 되면 가속 상수 원래대로 되돌리기
	GObjectTable->GetActorManager()->BroadcastSkillResult( id, ClassSkill::MOVE_FAST );

	// 스킬 썼으면 쿨 적용시키자
	SetCooldown( ClassSkill::MOVE_FAST );

	return true;
}

void Striker::DoPeriodWork( float dTime )
{
	if ( m_RemainFastMove > 0.0f )
	{
		m_RemainFastMove -= dTime;
		
		if ( m_RemainFastMove <= 0.0f )
		{
			m_RemainFastMove = 0.0f;
			// m_SpeedConstant = DEFAULT_MOVE_CONSTANT;
			GObjectTable->GetInstance<Character>( m_FastMoveTarget )->SetSpeedConstant( SCOUT_MOVE_FAST_CONSTANT );
			
			// 조심해!!
			// 이벤트 끝났으니까 이것도 방송해서 동기화
		}
	}
}