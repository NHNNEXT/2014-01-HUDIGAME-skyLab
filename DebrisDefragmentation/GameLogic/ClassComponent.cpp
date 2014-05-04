#include "ClassComponent.h"
#include "Physics.h"
#include "Rigidbody.h"

ClassComponent::ClassComponent()
{
}


ClassComponent::~ClassComponent()
{
}



void ClassComponent::GoForward( D3DXVECTOR3 viewDirection, Rigidbody& rb )
{
	printf_s( "GAS : %d	OXYGEN : %d		HP : %d\n", m_Fuel, m_Oxygen, m_HP );
	if ( !CheckRemainGas( GAS_FOR_GOFORWARD ) )
	{
		return;
	}

	// 가속 시작 시점 기록 - 타임 스탬프로 문제 해결
	// 나중에는 타이머 만들어서 써볼까?
	m_AccelerationStartTime = timeGetTime();
	m_IsAccelerating = true;

	D3DXVECTOR3 normalVec( 0, 0, 0 );
	//D3DXVECTOR3 viewDirection( GetViewDirection() );
	//Physics::GetNormalVector( &viewDirection, &normalVec );
	D3DXVec3Normalize( &normalVec, &viewDirection );

	rb.m_Acceleration += ( normalVec * ACCELERATION_WEIGHT );
}

void ClassComponent::Stop( Rigidbody& rb )
{
	// 장비를 정지합니다. 어 안되잖아? 어? 저, 정지가 안 돼, 정지시킬 수가 없어. 안-돼!
	rb.m_Acceleration = ZERO_VECTOR3;
	rb.m_Velocity = ZERO_VECTOR3;
}

void ClassComponent::SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity, Rigidbody& rigidbody )
{
	rigidbody.m_SpinAngle = angularVelocity;
	rigidbody.m_SpinAxis = rotationAxis;
}

void ClassComponent::AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity, Rigidbody& rigidbody )
{
	// 조심해!!
	// 구현 중
}

void ClassComponent::StopSpin( Rigidbody& rigidbody )
{
	rigidbody.m_SpinAngle = 0.0f;
	rigidbody.m_SpinAxis = ZERO_VECTOR3;
}

bool ClassComponent::CheckRemainOxygen()
{
	if ( OXYGEN_COUNSUMED > m_Oxygen )
	{
		// 산소 부족시 체력 감소
		m_HP -= HEALTH_REDUCED_BY_OXYGEN_INSUFFICIENT; ///# 경계값 확인 잘 할 것
		
		return false;
	}
	else
	{
		// 산소가 충분하면
		m_Oxygen -= OXYGEN_COUNSUMED;
		return true;
	}
}

bool ClassComponent::CheckRemainGas( int gasWillBeUsed )
{
	if ( gasWillBeUsed > m_Fuel )
	{
		return false;
	}
	m_Fuel -= gasWillBeUsed;
	return true;

}
