﻿#pragma once

#include <array>
#include <d3dx9.h>
#include <map>

enum class CharacterClass : int
{
	NO_CLASS = -1,
	STRIKER,
	ENGINEER,
	PROTECTOR
};

enum class ChangeType : int
{
	NO_CHANGE = -1,

	KINETIC_STATE,
	CHARACTER_STATE,
	GAME_EVENT_SATE,
};

enum class ClassSkill : int
{
	NO_SKILL = -1,

	PUSH,
	OCCUPY,
	DESTROY,
	SHARE_FUEL,

	// STRIKER
	PULL,
	SET_MINE,
	MOVE_FAST,

	// PROTECTOR
	WARNING,
	SHARE_OXYGEN,
	EMP,

	// ENGINEER
	GATHER,
	SET_SHELTER,
	SET_DISPENSER,
};
const unsigned int BASIC_SKILL_NUMBER = 4;
const unsigned int TOTAL_SKILL_NUMBER = 13;

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

// JSON 파일에서 불러오기 위한 ISSModule 변수
const std::map<ISSModuleName, std::string> JSON_ISS_PART_NAME =
{
	{ ISSModuleName::PART0, "0" },
	{ ISSModuleName::PART1, "1" },
	{ ISSModuleName::PART2, "2" },
	{ ISSModuleName::PART3, "3" },
	{ ISSModuleName::PART4, "4" },
	{ ISSModuleName::PART5, "5" },
	{ ISSModuleName::PART6, "6" },
	{ ISSModuleName::PART7, "7" },
	{ ISSModuleName::PART8, "8" },
	{ ISSModuleName::PART9, "9" },
};

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

const std::array<D3DXVECTOR3, MODULE_NUMBER> CONTROL_POINT_POSITION
= {
	D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
	D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
	D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
	D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
	D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
	D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
	D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
	D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
	D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
	D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
};

const D3DXVECTOR3 CONTROL_POINT_AXIS_LENGTH = D3DXVECTOR3( 0.5f, 0.5f, 0.5f );

const float ISS_MOVE_WEIGHT = 0.1f;
const float ISS_BASE_DAMAGE = 0.1f;

// 각 모듈의 초기 위치(모델), 충돌상자 중심점, 충돌상자의 각 축에 대한 길이, 

const int			NOTHING = -1;

// debris 관련
const D3DXVECTOR3	DEBRIS_AXIS_LEN{ 1.0f, 1.0f, 1.0f };
const int			DEBRIS_SPREAD_RANGE = 100;
const float			RESOURCE_DEBRIS_SCALE = 1.0f;
const int			RESOURCE_DEBRIS_NUMBER = 30;
const float			BACKGROUND_DEBRIS_SCALE = .1f;
const float			DEBRIS_TO_RESOURCE_AMOUNT = 100.0f;	//debris채취할 때마다 늘어나는 자원량


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
const float			DEFAULT_OXYGEN_SHARE_AMOUNT = 1000;
const float			DEFAULT_MOVE_CONSTANT = 1.0f;

// SKILL
const float			SKILL_RANGE = 50.0f;
const float			SCOUT_MOVE_FAST_CONSTANT = 2.0f;
const float			SCOUT_MOVE_FAST_DURATION = 5.0f;
const float			EMP_TIME = 2.0f;
const float			SPACE_MINE_RANGE = 50.0f;
const float			SPACE_MINE_FORCE = 1.0f;

// Cooldown time
// 모든 스킬은 cooldown time을 가지고 있고, 이 값이 0이 되면 즉시 쓸 수 있다.
// 각 각의 스킬을 쓰면 이 수치가 증가하게 되고 시간에 비례해서 감소하게 된다
// 모든 스킬은 global cooldown time을 공유한다
// EMP같은 스킬(와우 도적의 발차기)을 맞으면 global cooldowm time이 증가
// cooldown time은 매 프레임 dt를 기준으로 감소 시키므로 초단위로 생성할 것
const float			COOLDOWN_GLOBAL = 1.0f;
const std::array<float, TOTAL_SKILL_NUMBER> SKILL_COOLDOWN_TABLE
= {
	1.0f,	// COOLDOWN_PUSH
	1.0f,	// COOLDOWN_OCCUPY
	1.0f,	// COOLDOWN_DESTROY
	1.0f,	// COOLDOWN_SHARE_FUEL

	1.0f,	// COOLDOWN_PULL
	1.0f,	// COOLDOWN_SET_MINE
	1.0f,	// COOLDOWN_MOVE_FAST

	1.0f,	// COOLDOWN_WARNING
	1.0f,	// COOLDOWN_SHARE_OXYGEN
	1.0f,	// COOLDOWN_EMP

	1.0f,	// COOLDOWN_GATHER
	1.0f,	// COOLDOWN_SET_SENTRY_GUN
	1.0f,	// COOLDOWN_SET_DESPENSER
};


/*
	const float			COOLDOWN_PUSH = 1.0f;
	const float			COOLDOWN_OCCUPY = 1.0f;
	const float			COOLDOWN_DESTROY = 1.0f;
	const float			COOLDOWN_SHARE_FUEL = 1.0f;

	const float			COOLDOWN_PULL = 1.0f;
	const float			COOLDOWN_SET_MINE = 1.0f;
	const float			COOLDOWN_MOVE_FAST = 1.0f;

	const float			COOLDOWN_WARNING = 1.0f;
	const float			COOLDOWN_SHARE_OXYGEN = 1.0f;
	const float			COOLDOWN_EMP = 1.0f;

	const float			COOLDOWN_GATHER = 1.0f;
	const float			COOLDOWN_SET_SENTRY_GUN = 1.0f;
	const float			COOLDOWN_SET_DESPENSER = 1.0f;
*/

enum class GameEvent : int
{
	// 
	NO_EVENT = -1,
	DEBRIS_STORM,
	SOLAR_WIND,
};