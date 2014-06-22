#pragma once

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
	DISASTER_EVENT_STATE,
	RESOURCE_GATHER,
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
// -------------------------------- 삭제예정 --------------------------------
// 
// const std::array<D3DXVECTOR3, MODULE_NUMBER> ISS_MODULE_POSITION
// = {
// 	D3DXVECTOR3( -0.75f, 7.5f, -12.5f ),
// 	D3DXVECTOR3( -0.75f, 7.5f, 12.5f ),
// 	D3DXVECTOR3( -0.75f, 4.5f, -5.5f ),
// 	D3DXVECTOR3( -0.75f, 4.5f, 5.5f ),
// 	D3DXVECTOR3( -0.2f, 10.2f, 0.5f ),
// 	D3DXVECTOR3( -0.2f, 7.3f, 0.0f ),
// 	D3DXVECTOR3( -0.2f, 4.6f, 0.0f ),
// 	D3DXVECTOR3( -0.2f, 3.1f, 0.0f ),
// 	D3DXVECTOR3( -0.2f, 1.7f, 0.0f ),
// 	D3DXVECTOR3( -0.2f, -0.3f, 0.0f ),
// };
// 
// const std::array<D3DXVECTOR3, MODULE_NUMBER> ISS_MODULE_AXIS_LENGTH
// = {
// 	D3DXVECTOR3( 0.5f, 10.5f, 3.5f ),
// 	D3DXVECTOR3( 0.5f, 10.5f, 3.5f ),
// 	D3DXVECTOR3( 0.5f, 3.0f, 1.5f ),
// 	D3DXVECTOR3( 0.5f, 3.0f, 1.5f ),
// 	D3DXVECTOR3( 0.8f, 0.7f, 2.5f ),
// 	D3DXVECTOR3( 0.8f, 2.0f, 0.5f ),
// 	D3DXVECTOR3( 0.8f, 0.5f, 2.1f ),
// 	D3DXVECTOR3( 0.8f, 0.7f, 0.5f ),
// 	D3DXVECTOR3( 0.8f, 0.5f, 3.5f ),
// 	D3DXVECTOR3( 0.8f, 1.4f, 0.5f ),
// };
// -------------------------------- 절 취 선 --------------------------------

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

const float			DISPENSER_PRICE = 300.0f;
const float			DISPENSER_DEFAULT_OXYGEN = 5000.0f;
const float			DISPENSER_DEFAULT_FUEL = 5000.0f;
const float			DISPENSER_OXYGEN_INCREASE = 100.0f;
const float			DISPENSER_FUEL_INCREASE = 100.0f;
const float			DISPENSER_OXYGEN_EFFICIENCY = 1000.0f;
const float			DISPENSER_FUEL_EFFICIENCY = 1000.0f;

const float			DISPENSER_RANGE = 10.0f;

// 오브젝트 Scale 저장
const float			ISS_SCALE = 8.0f;
const float			SPACE_MINE_SCALE = 0.3f;
const float			DISPENSER_SCALE = 0.1f;
const float			CHARACTER_SCALE = 0.01f;

// 게임 셋팅
const unsigned int	REAL_PLAYER_NUM = 8;	// 더미를 제외한 실제 플레이어 수
const unsigned int	MAX_PLAYER_NUM = REAL_PLAYER_NUM * 2; // 더미 플레이어 수에 맞추도록 * 2함
const float			ACCELERATION_WEIGHT = 1.0f;
const float			PUSHPULL_WEIGHT = 5.0f;
const float			COLLISION_ACCELERATION_WEIGHT = 0.5f;
const unsigned int	ACCELERATION_TIME = 500;
const float			DEFAULT_SPIN_ANGULAR_VELOCITY = 1.0f;

#define				BLUE_TEAM_POSITION	D3DXVECTOR3(-100.0f, .0f, .0f)
#define				RED_TEAM_POSITION	D3DXVECTOR3(100.0f, .0f, .0f)
#define				BLUE_TEAM_ROTATION	D3DXVECTOR3(.0f, 90.0f, .0f)
#define				RED_TEAM_ROTATION	D3DXVECTOR3(.0f, 270.0f, .0f)

const D3DXVECTOR3	PLAYER_POSITIONS[REAL_PLAYER_NUM] = { 
	D3DXVECTOR3{ 0.0f, 10.0f, 10.0f }, 
	D3DXVECTOR3{ 0.0f, 0.0f, 10.0f },
	D3DXVECTOR3{ 0.0f, -10.0f, 10.0f },
	D3DXVECTOR3{ 0.0f, -10.0f, 0.0f },
	D3DXVECTOR3{ 0.0f, -10.0f, -10.0f },
	D3DXVECTOR3{ 0.0f, 0.0f, -10.0f },
	D3DXVECTOR3{ 0.0f, 10.0f, -10.0f },
	D3DXVECTOR3{ 0.0f, 10.0f, 0.0f }
};


const float			WINNING_DISTANCE = 50.0f;

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
const float			OXYGEN_CONSUMPTION_UNDER_DISASTER = OXYGEN_CONSUMPTION * 20.0f;
const float			HEALTH_REDUCED_BY_OXYGEN_INSUFFICIENT = 10.0f;
const float			FUEL_FOR_GOFORWARD = 30.0f;

const float			DEFAULT_OXYGEN = 10000.0f;
const float			DEFAULT_FUEL = 5000.0f;
const float			DEFAULT_HP = 100.0f;
const float			DEFAULT_FUEL_SHARE_AMOUNT = 1000;
const float			DEFAULT_OXYGEN_SHARE_AMOUNT = 1000;
const float			DEFAULT_MOVE_CONSTANT = 1.0f;

// SKILL
const float			PUSH_WEIGHT = 3.0f;
const float			SKILL_RANGE = 50.0f;
const float			SCOUT_MOVE_FAST_CONSTANT = 2.0f;
const float			SCOUT_MOVE_FAST_DURATION = 5.0f;
const float			EMP_TIME = 2.0f;
const float			SPACE_MINE_RANGE = 10.0f;
const float			SPACE_MINE_FORCE = 5.0f;
const int			MAX_DISPENSER_NUMBER = 1;
const int			MAX_SPACE_MINE_NUMBER = 2;

// 속도 및 이동 범위 제한
const float			DEFAULT_PLAYER_SPEED = 1.0f;
const float			MAX_PLAYER_SPEED = 20.0f;
const float			MAX_DISTANCE_FROM_ORIGIN = 350.0f;

// Cooldown time
// 모든 스킬은 cooldown time을 가지고 있고, 이 값이 0이 되면 즉시 쓸 수 있다.
// 각 각의 스킬을 쓰면 이 수치가 증가하게 되고 시간에 비례해서 감소하게 된다
// 모든 스킬은 global cooldown time을 공유한다
// EMP같은 스킬(와우 도적의 발차기)을 맞으면 global cooldowm time이 증가
// cooldown time은 매 프레임 dt를 기준으로 감소 시키므로 초단위로 생성할 것
const float			COOLDOWN_GLOBAL = 1.0f;
const float			COOLDOWN_STUN = 3.0f;
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


enum class GameEvent : int
{
	// 
	NO_EVENT = -1,
	DEBRIS_STORM,
	SOLAR_WIND,
	NUMBER_OF_DISASTORS,
};

enum class StructureType : int
{
	NO_STRUCTURE = -1,
	DISPENSER,
	SHELTER,
	SPACE_MINE,
};


struct ColorRange
{
	//ColorRange() : m_RMin( 0.0f ), m_RMax( 1.0f ), m_GMin( 0.0f ), m_GMax( 1.0f ), m_BMin( 0.0f ), m_BMax( 1.0f ), m_Alpha( 1.0f ) {}
	float m_RMin;
	float m_RMax;
	float m_GMin;
	float m_GMax;
	float m_BMin;
	float m_BMax;
	float m_Alpha;
};

const D3DXVECTOR3	EARTH_POSITION{ 0, -800, 0 };

const int			PARTICLE_EFFECT_BUFFER = 10;
const D3DXVECTOR3	TEMP_ORIGIN = EARTH_POSITION;
const float			FIREWORK_SIZE = 0.25f;

enum class EffectType : int
{
	EXPLOSION = 0,
	HEALING,
	DEBRIS_STRIKE,
};

// 파티클의 방향, 속도, 색상, 생존시간 등을 결정, 
// 색상의 경우 RGB 각각이 0.0f~1.0f 사이에서 랜덤하게 결정됨. 맨 마지막은 alpha값
const int			NUMBER_OF_PARTICLES = 100;

const float			EXPLOSION_LIFETIME = 1.0f;
const float			EXPLOSION_PARTICLE_VELOCITY = 20.0f;
const D3DXVECTOR3	EXPLOSION_DIR_MIN{ -1.0f, -1.0f, -1.0f };
const D3DXVECTOR3	EXPLOSION_DIR_MAX{ 1.0f, 1.0f, 1.0f };
const ColorRange	EXPLOSION_COLOR_RANGE = { 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f };

const float			HEALING_LIFETIME = 1.0f;
const float			HEALING_PARTICLE_VELOCITY = 1.0f;
const D3DXVECTOR3	HEALING_DIR_MIN{ -1.0f, 1.0f, -1.0f };
const D3DXVECTOR3	HEALING_DIR_MAX{ 1.0f, 1.0f, 1.0f };
const ColorRange	HEALING_COLOR_RANGE = { 0.1f, 0.2f, 0.8f, 1.0f, 0.2f, 0.3f, 1.0f };

const int			NUMBER_OF_DS_PARTICLES = 1000;
const float			DS_LIFETIME = 10.0f;
const float			DS_PARTICLE_VELOCITY = 500.0f;
const D3DXVECTOR3	DS_DIR_MIN{ -1.0f, 0.0f, -1.0f };
const D3DXVECTOR3	DS_DIR_MAX{ 1.0f, 0.0f, 1.0f };
const D3DXVECTOR3	DS_ORIGIN_MIN{ -1000.0f, -1000.0f, -1000.0f };
const D3DXVECTOR3	DS_ORIGIN_MAX{ 1000.0f, 1000.0f, 1000.0f };
const ColorRange	DS_COLOR_RANGE = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

const D3DXVECTOR3	DIRECTION_OFFSET{ 0.2f, 0.2f, 0.2f };

// D3DXVECTOR3 mapMin{ -1000.0f, -1000.0f, -1000.0f };
// D3DXVECTOR3 mapMax{ 1000.0f, 1000.0f, 1000.0f };

// SCENE 종류 지정
enum class SceneType : int
{
	PLAY_SCENE = 0,
	LOADING_SCENE,
	RESULT_SCENE,
};