#pragma once

#include "GameConfig.h"

// 강체 변환관련 변수들을 가짐, 연산은 Physics에서..
// 4.21 김성환
struct RIGIDBODY
{
	float		mass = 1.0f;
	D3DXVECTOR3	acceleration{ 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3	velocity{ 0.0f, 0.0f, 0.0f };
};