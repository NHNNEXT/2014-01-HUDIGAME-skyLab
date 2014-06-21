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
	Character* skillUserCharacter = GObjectTable->GetCharacter( id );
	assert( skillUserCharacter );

	Character* targetCharacter = GObjectTable->GetCharacter( targetId );
	assert( targetCharacter );

	D3DXVECTOR3 force = targetCharacter->GetTransform()->GetPosition() - skillUserCharacter->GetTransform()->GetPosition();

	// 변화 적용
	targetCharacter->Move( -force );
	targetCharacter->SetSpin( spinAxis, DEFAULT_SPIN_ANGULAR_VELOCITY );
	targetCharacter->GetClassComponent()->SetMovementControlCooldown( COOLDOWN_STUN );

	GObjectTable->GetActorManager()->BroadcastCharacterChange( targetId, ChangeType::KINETIC_STATE );
	
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

	Character* skillUserCharacter = GObjectTable->GetCharacter( id );
	assert( skillUserCharacter );

	D3DXVECTOR3 viewDirection = skillUserCharacter->GetViewDirection( direction );
	D3DXVec3Normalize( &viewDirection, &viewDirection );
	D3DXVECTOR3	startPoint = skillUserCharacter->GetTransform()->GetPosition();

	// 스킬 사용 방향에 있는 모듈 검색
	ISSModuleName targetModuleName = iss->ModuleOnRay( viewDirection, startPoint );
	
	if ( targetModuleName == ISSModuleName::NO_MODULE )
		return false;
	
	ISSModule* targetModule = iss->GetModule( targetModuleName );
	float distance = std::numeric_limits<float>::infinity();
	Physics::IntersectionCheckRayBox( nullptr, &distance, nullptr, viewDirection, startPoint, targetModule->GetCollisionBox() );

	// 모듈까지의 거리 체크 - 멀면 return false;
	if ( distance > SKILL_RANGE )
		return false;

	// 그렇지 않으면 바운딩 박스와 ray의 교점 위치에
	// ray 방향의 반대 방향을 정면으로 설정
	// actorManager에 등록
	D3DXVECTOR3 minePosition = startPoint + viewDirection * distance;
	GObjectTable->GetActorManager()->InstallMine( minePosition, -viewDirection, skillUserCharacter->GetTeam(), id );

	// 설치 완료
	printf_s( "space mine installed \n" );

	return true;
}

bool Striker::SkillMoveFast( int id, const D3DXVECTOR3& direction )
{
	// 쿨탐 체크
	if ( m_GlobalCooldown > 0.0f || m_CooldownTable[static_cast<int>( ClassSkill::MOVE_FAST )] > 0.0f )
		return false;

	Character* skillUserCharacter = GObjectTable->GetCharacter( id );
	assert( skillUserCharacter );

	skillUserCharacter->SetSpeedConstant( SCOUT_MOVE_FAST_CONSTANT );
	m_RemainFastMove = SCOUT_MOVE_FAST_DURATION;
	m_FastMoveTarget = id;

	// 일단 쿨탐과 같은 방식으로 진행하자
	// 스킬 쓰면 시간을 설정하고 dt만큼 감소 시키다가 0이 되면 가속 상수 원래대로 되돌리기
	GObjectTable->GetActorManager()->BroadcastCharacterChange( id, ChangeType::CHARACTER_STATE );

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

			Character* targetCharacter = GObjectTable->GetCharacter( m_FastMoveTarget );
			assert( targetCharacter );

			targetCharacter->SetSpeedConstant( DEFAULT_MOVE_CONSTANT );
			GObjectTable->GetActorManager( )->BroadcastCharacterChange( m_FastMoveTarget, ChangeType::CHARACTER_STATE );
		}
	}
}