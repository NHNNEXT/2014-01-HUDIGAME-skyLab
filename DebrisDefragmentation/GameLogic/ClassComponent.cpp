#include "stdafx.h"
#include "ClassComponent.h"
#include "Physics.h"
#include "Rigidbody.h"
#include "ActorManager.h"
#include "Character.h"
#include "ObjectTable.h"
#include"Striker.h"
#include "Engineer.h"
#include "Protector.h"

ClassComponent::ClassComponent()
{
	m_CooldownTable.fill( 0.0f );
}


ClassComponent::~ClassComponent()
{
}

std::shared_ptr<ClassComponent> ClassComponent::Create( CharacterClass className )
{
	switch ( className )
	{
	case CharacterClass::STRIKER:
		return Striker::Create();
		break;
	case CharacterClass::ENGINEER:
		return Engineer::Create();
		break;
	case CharacterClass::PROTECTOR:
		return Protector::Create();
		break;
	default:
		assert( false );
		break;
	}

	return std::shared_ptr<ClassComponent>( nullptr );
}


bool ClassComponent::SkillGoForward( int id, D3DXVECTOR3 viewDirection )
{
	printf_s( "GAS : %0.2f	OXYGEN : %0.2f		HP : %0.2f\n", m_Fuel, m_Oxygen, m_HP );
	if ( !UseFuel( FUEL_FOR_GOFORWARD ) )
	{
		return false;
	}

	// 이상하지만 자신을 가지고 있는 actor를 찾아서 움직임을 반영한다.
	Character* targetCharacter = GObjectTable->GetCharacter( id );
	assert( targetCharacter );

	targetCharacter->Move( viewDirection );

	return true;
}

void ClassComponent::SkillStop( int id )
{
	Character* targetCharacter = GObjectTable->GetCharacter( id );
	assert( targetCharacter );

	targetCharacter->Stop();
}

void ClassComponent::SkillTurnBody( int id,float x, float y, float z )
{ 
	// 여기서 상위에 이 움직임을 적용해야 한다.
	// 자신의 Actor*를 찾아서 ->TurnBody(tr, x, y, z); 
	Character* targetCharacter = GObjectTable->GetCharacter( id );
	assert( targetCharacter );

	targetCharacter->GetTransform()->SetRotation( x, y, z );
}

bool ClassComponent::SkillPush( int id, const D3DXVECTOR3& direction )
{
	printf_s( "try to push\n" );

	// 쿨탐 체크
	if ( m_GlobalCooldown > 0.0f || m_CooldownTable[static_cast<int>(ClassSkill::PUSH)] > 0.0f )
		return false;

	printf_s( "no cooldown\n" );

	int targetId = NOTHING;
	D3DXVECTOR3 spinAxis;

	// 타겟을 검출한다.
	std::tie( targetId, spinAxis ) = GObjectTable->GetActorManager()->DetectTarget( id, direction );

	if ( targetId == NOTHING )
		return false;

	printf_s( "target : %d\n", targetId );

	Character* skillUserCharacter = GObjectTable->GetCharacter( id );
	assert( skillUserCharacter );

	Character* targetCharacter = GObjectTable->GetCharacter( targetId );
	assert( targetCharacter );

	// 타겟이 있으므로 스킬 결과를 반영한다.
	D3DXVECTOR3 force = targetCharacter->GetTransform()->GetPosition() - skillUserCharacter->GetTransform()->GetPosition();
	
	// 변화 적용
	targetCharacter->Move( force );
	targetCharacter->SetSpin( spinAxis, DEFAULT_SPIN_ANGULAR_VELOCITY );

	GObjectTable->GetActorManager()->BroadcastCharacterChange( targetId, ChangeType::KINETIC_STATE );

	// 스킬 썼으면 쿨 적용시키자
	SetCooldown( ClassSkill::PUSH );

	return true;
}

bool ClassComponent::SkillShareFuel( int id, const D3DXVECTOR3& direction )
{
	// 쿨탐 체크
	if ( m_GlobalCooldown > 0.0f || m_CooldownTable[static_cast<int>( ClassSkill::SHARE_FUEL )] > 0.0f )
		return false;

	int targetId = NOTHING;
	D3DXVECTOR3 spinAxis; // 사용은 안 함

	// 나눠 줄 연료가 없다ㅠ
	if ( m_Fuel < DEFAULT_FUEL_SHARE_AMOUNT )
		return false;

	std::tie( targetId, spinAxis ) = GObjectTable->GetActorManager()->DetectTarget( id, direction );

	// 타겟이 없으면 그냥 무시
	if ( targetId == NOTHING )
		return false;

	Character* skillUserCharacter = GObjectTable->GetCharacter( id );
	assert( skillUserCharacter );

	Character* targetCharacter = GObjectTable->GetCharacter( targetId );
	assert( targetCharacter );

	if ( skillUserCharacter->GetTeam() != targetCharacter->GetTeam() )
		return false;

	m_Fuel -= DEFAULT_FUEL_SHARE_AMOUNT;
	targetCharacter->GetClassComponent()->IncreaseFuel( DEFAULT_FUEL_SHARE_AMOUNT );

	GObjectTable->GetActorManager()->BroadcastCharacterChange( targetId, ChangeType::CHARACTER_STATE );

	// 스킬 썼으면 쿨 적용시키자
	SetCooldown( ClassSkill::SHARE_FUEL );

	return true;
}

bool ClassComponent::SkillOccupy( int id, const D3DXVECTOR3& direction )
{
	// 쿨탐 체크
	if ( m_GlobalCooldown > 0.0f || m_CooldownTable[static_cast<int>( ClassSkill::OCCUPY )] > 0.0f )
	{
		printf_s( "COOLDOWN : %f / %f\n", m_GlobalCooldown, m_CooldownTable[static_cast<int>( ClassSkill::OCCUPY )] );
		return false;
	}

	// 판정은 GActorManager에 맞기자
	// 방송도 GActorManager가 OccupyISS 진행하면서 하는 걸로
	bool returnVal = GObjectTable->GetActorManager()->GetIss()->Occupy( id, direction );

	// 스킬 썼으면 쿨 적용시키자
	if ( returnVal )
		SetCooldown( ClassSkill::OCCUPY );

	return returnVal;
}

bool ClassComponent::SkillDestroy( int id, const D3DXVECTOR3& direction )
{
	// 쿨탐 체크
	if ( m_GlobalCooldown > 0.0f || m_CooldownTable[static_cast<int>( ClassSkill::DESTROY )] > 0.0f )
		return false;

	// 판정은 GActorManager에 맞기자
	// 방송도 GActorManager가 DestroyISS 진행하면서 하는 걸로
	bool returnVal = GObjectTable->GetActorManager()->GetIss()->Destroy( id, direction );

	// 스킬 썼으면 쿨 적용시키자
	if ( returnVal )
		SetCooldown( ClassSkill::DESTROY );

	return returnVal;
}

bool ClassComponent::UseOxygen( float oxygenUse )
{
	//printf_s( "oxygen use : %0.2f\n", oxygenUse );
	if ( oxygenUse > m_Oxygen )
	{
		// 산소 부족시 체력 감소
		m_HP -= HEALTH_REDUCED_BY_OXYGEN_INSUFFICIENT;
		m_HP = ( m_HP < 0 ) ? 0 : m_HP;
		
		return false;
	}
	else
	{
		// 산소가 충분하면
		m_Oxygen -= oxygenUse;
		return true;
	}
}

bool ClassComponent::UseFuel( float fuelUse )
{
	if ( fuelUse > m_Fuel )
	{
		return false;
	}

	m_Fuel -= fuelUse;
	m_Fuel = ( m_Fuel < 0.0f ) ? 0.0f : m_Fuel;

	return true;

}

void ClassComponent::Update( float dt )
{
	// 기본 산소 소모
	UseOxygen( dt * OXYGEN_CONSUMPTION );
	
	if ( m_DispenserEffectFlag )
	{
		m_Oxygen += dt * DISPENSER_OXYGEN_EFFICIENCY;
		m_Fuel += dt * DISPENSER_FUEL_EFFICIENCY;
	}
	

	// 쿨타임 업데이트
	m_GlobalCooldown -= dt;
	if ( m_GlobalCooldown < 0.0f )
		m_GlobalCooldown = 0.0f;

	std::for_each( m_CooldownTable.begin(), m_CooldownTable.end(), [&]( float& eachCooldown )
	{
		eachCooldown -= dt;

		if ( eachCooldown < 0.0f )
			eachCooldown = 0.0f;
	} 
	);

	DoPeriodWork( dt );
}

void ClassComponent::ResetStatus()
{
	SetOxygen( DEFAULT_OXYGEN );
	SetHP( DEFAULT_HP );
	SetFuel( DEFAULT_FUEL );
}

void ClassComponent::SetCooldown( ClassSkill skillType )
{
	m_GlobalCooldown = COOLDOWN_GLOBAL;
	m_CooldownTable[static_cast<int>( skillType )] = SKILL_COOLDOWN_TABLE[static_cast<int>( skillType )];
}