#include "stdafx.h"
#include "ClassComponent.h"
#include "Physics.h"
#include "Rigidbody.h"
#include "ActorManager.h"
#include "Character.h"
#include "ObjectTable.h"
#include "Engineer.h"

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
	case CharacterClass::ENGINEER:
		return Engineer::Create();
		break;
	default:
		assert( false );
		break;
	}

	return std::shared_ptr<ClassComponent>( nullptr );
}


bool ClassComponent::SkillGoForward( int id, D3DXVECTOR3 viewDirection )
{
	// 쿨탐 체크
	if ( m_MovementControlCooldown > 0.0f || m_GlobalCooldown > 0.0f )
		return false;

	printf_s( "GAS : %0.2f	OXYGEN : %0.2f		HP : %0.2f\n", m_Fuel, m_Oxygen, m_HP );
	if ( !UseFuel( FUEL_FOR_GOFORWARD ) )
	{
		return false;
	}

	// 이상하지만 자신을 가지고 있는 actor를 찾아서 움직임을 반영한다.
	Character* targetCharacter = GObjectTable->GetCharacter( id );
	assert( targetCharacter );

	targetCharacter->Move( viewDirection );
	
	// 여기서 한번 상태 방송해줘야 fuel이 줄어들 것 같음..
	GObjectTable->GetActorManager()->BroadcastCharacterChange( id, ChangeType::CHARACTER_STATE );

	m_GlobalCooldown = COOLDOWN_GLOBAL;

	return true;
}

bool ClassComponent::SkillStop( int id )
{
	// 쿨탐 체크
	if ( m_MovementControlCooldown > 0.0f )
		return false;

	Character* targetCharacter = GObjectTable->GetCharacter( id );
	assert( targetCharacter );

	targetCharacter->Stop();

	return true;
}

bool ClassComponent::SkillTurnBody( int id, D3DXVECTOR3 direction )
{ 
	// 쿨탐 체크
	if ( m_MovementControlCooldown > 0.0f )
		return false;

	// 여기서 상위에 이 움직임을 적용해야 한다.
	// 자신의 Actor*를 찾아서 ->TurnBody(tr, x, y, z); 
	Character* targetCharacter = GObjectTable->GetCharacter( id );
	assert( targetCharacter );

	targetCharacter->GetTransform()->SetRotation( direction );

	return true;
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
	targetCharacter->GetClassComponent()->SetMovementControlCooldown( COOLDOWN_STUN );

	GObjectTable->GetActorManager()->BroadcastCharacterChange( targetId, ChangeType::KINETIC_STATE );

	// 스킬 썼으면 쿨 적용시키자
	SetCooldown( ClassSkill::PUSH );

	return true;
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

	// 쿨타임 업데이트
	m_MovementControlCooldown -= dt;
	if ( m_MovementControlCooldown < 0.0f )
		m_MovementControlCooldown = 0.0f;
	
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