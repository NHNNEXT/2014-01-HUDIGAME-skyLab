#pragma once

#include "GameOption.h"
#include "GameMacro.h"

// 강체 변환관련 변수들을 가짐, 연산은 Physics에서..
struct Rigidbody
{
	void Init()
	{
		ZeroMemory( this, sizeof( Rigidbody ) );
		m_Mass = DEFAULT_MASS;
		m_Acceleration = ZERO_VECTOR3;
		m_Velocity = ZERO_VECTOR3;
		m_SpinAxis = ZERO_VECTOR3;
		m_SpinAngularVelocity = 0.0f;

		m_IsAccelerating = false;
		m_IsSpin = false;
	}

	float		m_Mass = DEFAULT_MASS;
	D3DXVECTOR3	m_Acceleration = ZERO_VECTOR3;
	D3DXVECTOR3	m_Velocity = ZERO_VECTOR3;
	D3DXVECTOR3	m_SpinAxis = ZERO_VECTOR3;
	float		m_SpinAngularVelocity = 0.0f;

	bool		m_IsAccelerating = false;
	bool		m_IsSpin = false;
};