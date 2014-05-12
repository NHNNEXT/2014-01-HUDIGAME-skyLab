#include "stdafx.h"
#include "ClassComponent.h"
#include "Physics.h"
#include "Rigidbody.h"

ClassComponent::ClassComponent()
{
}


ClassComponent::~ClassComponent()
{
}



bool ClassComponent::GoForward( D3DXVECTOR3 viewDirection )
{
	printf_s( "GAS : %d	OXYGEN : %d		HP : %d\n", m_Fuel, m_Oxygen, m_HP );
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

void ClassComponent::SkillPush( ClassComponent& targetComponent, D3DXVECTOR3 force )
{
	targetComponent.AddForce( force );
}

void ClassComponent::SkillPull( ClassComponent& targetComponent, D3DXVECTOR3 force )
{
	targetComponent.AddForce( -force );
}

void ClassComponent::SkillShareFuel( ClassComponent& targetComponent )
{
	m_Fuel -= DEFAULT_FUEL_SHARE_AMOUNT;
	targetComponent.IncreaseFuel( DEFAULT_FUEL_SHARE_AMOUNT );
}

void ClassComponent::SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity )
{
	m_Rigidbody.m_SpinAngle = angularVelocity;
	m_Rigidbody.m_SpinAxis = rotationAxis;
}

void ClassComponent::AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity )
{
	// 조심해!!
	// 구현 중
}

void ClassComponent::StopSpin()
{
	m_Rigidbody.m_SpinAngle = 0.0f;
	m_Rigidbody.m_SpinAxis = ZERO_VECTOR3;
}

bool ClassComponent::UseOxygen( float oxygenUse )
{
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
	m_Fuel = ( m_Fuel < 0 ) ? 0 : m_Fuel;

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
	UseOxygen( dt * DEFAULT_CONSUMPTION );
}