#pragma once

#include <array>
#include <d3dx9.h>

enum class CharacterClass : int
{
	NO_CLASS = -1,
	STRIKER,
	ENGINEER,
	PROTECTOR
};


// ISS
enum class TeamColor : int
{
	NO_TEAM = -1,
	BLUE,
	RED
};

enum class ISSModuleName : int
{
	// 이름 의미있는 걸로 바꾸는 게 좋을까
	// 하지만 실제 ISS 이름은 PART1보다 더 이해하기 어려운 이름인 게 함정 ㅋㅋ
	NO_MODULE = -1,
	PART0,
	PART1,
	PART2,
	PART3,
	PART4,
	PART5,
	PART6,
	PART7,
	PART8,
	PART9,
};
const unsigned int	MODULE_NUMBER = 10;

const std::array<D3DXVECTOR3, MODULE_NUMBER> ISS_MODULE_POSITION
= {
	D3DXVECTOR3( -0.75f, 7.5f, -12.5f ),
	D3DXVECTOR3( -0.75f, 7.5f, 12.5f ),
	D3DXVECTOR3( -0.75f, 4.5f, -5.5f ),
	D3DXVECTOR3( -0.75f, 4.5f, 5.5f ),
	D3DXVECTOR3( -0.2f, 10.2f, 0.5f ),
	D3DXVECTOR3( -0.2f, 7.3f, 0.0f ),
	D3DXVECTOR3( -0.2f, 4.6f, 0.0f ),
	D3DXVECTOR3( -0.2f, 3.1f, 0.0f ),
	D3DXVECTOR3( -0.2f, 1.7f, 0.0f ),
	D3DXVECTOR3( -0.2f, -0.3f, 0.0f ),
};

const std::array<D3DXVECTOR3, MODULE_NUMBER> ISS_MODULE_AXIS_LENGTH
= {
	D3DXVECTOR3( 0.5f, 10.5f, 3.5f ),
	D3DXVECTOR3( 0.5f, 10.5f, 3.5f ),
	D3DXVECTOR3( 0.5f, 3.0f, 1.5f ),
	D3DXVECTOR3( 0.5f, 3.0f, 1.5f ),
	D3DXVECTOR3( 0.8f, 0.7f, 2.5f ),
	D3DXVECTOR3( 0.8f, 2.0f, 0.5f ),
	D3DXVECTOR3( 0.8f, 0.5f, 2.1f ),
	D3DXVECTOR3( 0.8f, 0.7f, 0.5f ),
	D3DXVECTOR3( 0.8f, 0.5f, 3.5f ),
	D3DXVECTOR3( 0.8f, 1.4f, 0.5f ),
};

const float ISS_MOVE_WEIGHT = 0.1f;
const float ISS_BASE_DAMAGE = 0.1f;

// 각 모듈의 초기 위치(모델), 충돌상자 중심점, 충돌상자의 각 축에 대한 길이, 


// 게임 셋팅
const unsigned int	REAL_PLAYER_NUM = 8;	// 더미를 제외한 실제 플레이어 수
const unsigned int	MAX_PLAYER_NUM = REAL_PLAYER_NUM * 2; // 더미 플레이어 수에 맞추도록 * 2함
const float			ACCELERATION_WEIGHT = 1.0f;
const float			PUSHPULL_WEIGHT = 5.0f;
const float			COLLISION_ACCELERATION_WEIGHT = 0.5f;
const unsigned int	ACCELERATION_TIME = 500;
const float			DEFAULT_SPIN_ANGULAR_VELOCITY = 1.0f;

#define				BLUE_TEAM_POSITION	D3DXVECTOR3(100.0f, .0f, .0f)
#define				RED_TEAM_POSITION	D3DXVECTOR3(-100.0f, .0f, .0f)
#define				BLUE_TEAM_ROTATION	D3DXVECTOR3(.0f, 270.0f, .0f)
#define				RED_TEAM_ROTATION	D3DXVECTOR3(.0f, 90.0f, .0f)

const float			WINNING_DISTANCE = 150.0f;

// collision box
/*
const float			CHARACTER_CB_LENGTH_X = 0.5f;
const float			CHARACTER_CB_LENGTH_Y = 1.0f;
const float			CHARACTER_CB_LENGTH_Z = 0.65f;

const float			CHARACTER_CB_CENTER_POS_X = 0.0f;
const float			CHARACTER_CB_CENTER_POS_Y = -0.5f;
const float			CHARACTER_CB_CENTER_POS_Z = -0.2f;
*/
const float			CHARACTER_CB_LENGTH_X = 1.0f;
const float			CHARACTER_CB_LENGTH_Y = 1.0f;
const float			CHARACTER_CB_LENGTH_Z = 1.0f;

const float			CHARACTER_CB_CENTER_POS_X = 0.0f;
const float			CHARACTER_CB_CENTER_POS_Y = -0.5f;
const float			CHARACTER_CB_CENTER_POS_Z = 0.0f;


// 추진체 관련
const float			OXYGEN_CONSUMPTION = 100.0f;
const float			HEALTH_REDUCED_BY_OXYGEN_INSUFFICIENT = 10.0f;
const float			FUEL_FOR_GOFORWARD = 30.0f;

const float			DEFAULT_OXYGEN = 10000.0f;
const float			DEFAULT_FUEL = 5000.0f;
const float			DEFAULT_HP = 100.0f;
const float			DEFAULT_FUEL_SHARE_AMOUNT = 1000;


// SKILL
const float			SKILL_RANGE = 50;

