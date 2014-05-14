﻿#include "stdafx.h"
#include "ClassComponent.h"
#include "Physics.h"
#include "Rigidbody.h"
#include "ActorManager.h"
#include "Character.h"
#include "ObjectTable.h"

ClassComponent::ClassComponent()
{
}


ClassComponent::~ClassComponent()
{
}



bool ClassComponent::GoForward( D3DXVECTOR3 viewDirection )
{
	printf_s( "GAS : %0.2f	OXYGEN : %0.2f		HP : %0.2f\n", m_Fuel, m_Oxygen, m_HP );
	if ( !UseFuel( FUEL_FOR_GOFORWARD ) )
	{
		return false;
	}

	// 가속 시작 시점 기록 - 타임 스탬프로 문제 해결
	// 나중에는 타이머 만들어서 써볼까?
	m_AccelerationStartTime = timeGetTime();
	SetIsAccelerating(true);

	D3DXVECTOR3 normalVec( 0, 0, 0 );
	//D3DXVECTOR3 viewDirection( GetViewDirection() );
	//Physics::GetNormalVector( &viewDirection, &normalVec );
	D3DXVec3Normalize( &normalVec, &viewDirection );

	m_Rigidbody.m_Acceleration += ( normalVec * ACCELERATION_WEIGHT );

	return true;
}

void ClassComponent::Stop()
{
	// 장비를 정지합니다. 어 안되잖아? 어? 저, 정지가 안 돼, 정지시킬 수가 없어. 안-돼!
	m_Rigidbody.m_Acceleration = ZERO_VECTOR3;
	m_Rigidbody.m_Velocity = ZERO_VECTOR3;
}

bool ClassComponent::SkillPush( int id, const D3DXVECTOR3& direction )
{
	int targetId = NOTHING;
	D3DXVECTOR3 spinAxis;

	// 타겟을 검출한다.
	std::tie( targetId, spinAxis ) = GObjectTable->GetActorManager()->DetectTarget( id, direction );

	if ( targetId == NOTHING )
		return false;

	// 타겟이 있으므로 스킬 결과를 반영한다.
	D3DXVECTOR3 force = GObjectTable->GetInstance<Transform>( targetId )->GetPosition() - GObjectTable->GetInstance<Transform>( id )->GetPosition();
	
	// 변화 적용
	GObjectTable->GetInstance<ClassComponent>( targetId )->AddForce( force );
	GObjectTable->GetInstance<ClassComponent>( targetId )->SetSpin( spinAxis, DEFAULT_SPIN_ANGULAR_VELOCITY );

	GObjectTable->GetActorManager()->BroadcastSkillResult( targetId, ClassSkill::PUSH );

	return true;
}

bool ClassComponent::SkillShareFuel( int id, const D3DXVECTOR3& direction )
{
	int targetId = NOTHING;
	D3DXVECTOR3 spinAxis; // 사용은 안 함

	// 나눠 줄 연료가 없다ㅠ
	if ( GetFuel() < DEFAULT_FUEL_SHARE_AMOUNT )
		return false;

	std::tie( targetId, spinAxis ) = GObjectTable->GetActorManager()->DetectTarget( id, direction );

	// 타겟이 없으면 그냥 무시
	if ( targetId == NOTHING )
		return false;

	m_Fuel -= DEFAULT_FUEL_SHARE_AMOUNT;
	GObjectTable->GetInstance<ClassComponent>( targetId )->IncreaseFuel( DEFAULT_FUEL_SHARE_AMOUNT );

	GObjectTable->GetActorManager()->BroadcastSkillResult( targetId, ClassSkill::SHARE_FUEL );

	return true;
}

bool ClassComponent::SkillOccupy( int id, const D3DXVECTOR3& direction )
{
	// 판정은 GActorManager에 맞기자
	// 방송도 GActorManager가 OccupyISS 진행하면서 하는 걸로
	return GObjectTable->GetActorManager()->OccupyISS( id, direction );
}

bool ClassComponent::SkillDestroy( int id, const D3DXVECTOR3& direction )
{
	// 판정은 GActorManager에 맞기자
	// 방송도 GActorManager가 DestroyISS 진행하면서 하는 걸로
	return GObjectTable->GetActorManager()->DestroyISS( id, direction );
}

void ClassComponent::SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity )
{
	m_Rigidbody.m_SpinAngle = angularVelocity;
	m_Rigidbody.m_SpinAxis = rotationAxis;
	SetSpinTime( 0.0f );
	SetSpinnigFlag( true );
}

void ClassComponent::AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity )
{
	// 조심해!!
	// 구현 중
}

void ClassComponent::StopSpin()
{
	SetSpinnigFlag( false );
	SetSpinTime( 0.0f );
	m_Rigidbody.m_SpinAngle = 0.0f;
	m_Rigidbody.m_SpinAxis = ZERO_VECTOR3;
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

void ClassComponent::AddForce( const D3DXVECTOR3 &direction )
{
	SetAccelerationStartTime( timeGetTime() );
	SetIsAccelerating( true );

	D3DXVECTOR3 normalVec( ZERO_VECTOR3 );
	D3DXVec3Normalize( &normalVec, &direction );

	m_Rigidbody.m_Acceleration += ( normalVec * PUSHPULL_WEIGHT );
}

void ClassComponent::Update( float dt )
{
	// 기본 산소 소모
	UseOxygen( dt * OXYGEN_CONSUMPTION );

	// 가속
	if ( IsAccelerating() )
	{
		if ( timeGetTime() - GetAccelerationStartTime() > ACCELERATION_TIME )
		{
			// 가속 끝났다
			SetIsAccelerating( false );
			SetAcceleration( ZERO_VECTOR3 );
		}
	}
}

void ClassComponent::ResetStatus()
{
	SetOxygen( DEFAULT_OXYGEN );
	SetHP( DEFAULT_HP );
	SetFuel( DEFAULT_FUEL );
	SetVelocity( ZERO_VECTOR3 );

	m_SpinTime = 0;
	m_AccelerationStartTime = 0;
	m_Rigidbody.Init();
}
