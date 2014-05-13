#pragma once

#include "GameOption.h"

// 강체 변환관련 변수들을 가짐, 연산은 Physics에서..
// 4.21 김성환
struct Rigidbody
{
	void Init()
	{
		ZeroMemory( this, sizeof( Rigidbody ) );
		m_Mass = 1.0f;
	}
	float		m_Mass = 1.0f;
	D3DXVECTOR3	m_Acceleration{ 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3	m_Velocity{ 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3	m_SpinAxis{ 0.0f, 0.0f, 0.0f };
	float		m_SpinAngle = 0.0f;

	bool		m_IsAccelerating = false;
	bool		m_IsSpin = false;
};