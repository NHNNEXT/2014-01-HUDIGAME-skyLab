#pragma once
#include <string>
#include <array>
#include <d3dx9.h>

enum class CharacterClass : int
{
	NO_CLASS = -1,
	STRIKER,
	ENGINEER,
	PROTECTOR
};

enum class ClientUITag : int
{
	UI_OXYGEN_TAG,
	UI_FUEL_TAG,
	UI_FRAME_TAG,
	UI_TAG_COUNT // total UI 숫자
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
	/*
	D3DXVECTOR3( -0.75f, 0.0f, -12.5f ),
	D3DXVECTOR3( -0.75f, 0.0f, 12.5f ),
	D3DXVECTOR3( -0.75f, 2.5f, -5.5f ),
	D3DXVECTOR3( -0.75f, 2.5f, 5.5f ),
	D3DXVECTOR3( -0.2f, 2.7f, 0.5f ),
	D3DXVECTOR3( -0.2f, -0.2f, 0.0f ),
	D3DXVECTOR3( -0.2f, -2.9f, 0.0f ),
	D3DXVECTOR3( -0.2f, -4.4f, 0.0f ),
	D3DXVECTOR3( -0.2f, -5.8f, 0.0f ),
	D3DXVECTOR3( -0.2f, -7.8f, 0.0f ),
	*/
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

const float ISS_MOVE_WEIGHT = 5.0f;
const float ISS_BASE_DAMAGE = 0.1;

// 각 모듈의 초기 위치(모델), 충돌상자 중심점, 충돌상자의 각 축에 대한 길이, 


// 게임 셋팅
const unsigned int	MAX_PLAYER_NUM = 8 * 2; // 더미 플레이어 수에 맞추도록 * 2함
const unsigned int	REAL_PLAYER_NUM = 8;	// 더미를 제외한 실제 플레이어 수
const float			ACCELERATION_WEIGHT = 1.0f;
const float			COLLISION_ACCELERATION_WEIGHT = 0.5f;
const unsigned int	ACCELERATION_TIME = 500;

const int			VECTOR_DIRECTION_3 = 3;
const int			BOX_POINT_COUNT = 8;

#define				BLUE_TEAM_POSITION	D3DXVECTOR3(100.0f, .0f, .0f)
#define				RED_TEAM_POSITION	D3DXVECTOR3(-100.0f, .0f, .0f)
#define				BLUE_TEAM_ROTATION	D3DXVECTOR3(.0f, 270.0f, .0f)
#define				RED_TEAM_ROTATION	D3DXVECTOR3(.0f, 90.0f, .0f)


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
const int			OXYGEN_COUNSUMED = 1;
const int			HEALTH_REDUCED_BY_OXYGEN_INSUFFICIENT = 10;
const int			GAS_FOR_GOFORWARD = 30;

const int			DEFAULT_OXYGEN = 3000;
const int			DEFAULT_FUEL = 5000;
const int			DEFAULT_HP = 100;


// SKILL
const float			SKILL_RANGE = 50;


// UI
const float			UI_OXYGEN_POSITION_X = 10.0f;
const float			UI_OXYGEN_POSITION_Y = 10.0f;
const float			UI_FUEL_POSITION_X = 10.0f;
const float			UI_FUEL_POSITION_Y = 30.0f;
const float			UI_FRAME_POSITION_X = 0.0f;
const float			UI_FRAME_POSITION_Y = 50.0f;

const std::wstring	UI_FILE_PATH = L".\\Resources\\Image\\";
const std::array<std::wstring, size_t( ClientUITag::UI_TAG_COUNT )> UI_FILENAME_LIST
	= {
		L"OxygenUI.png",
		L"FuelUI.png",
		L"Frame.png"
	};


// Config
const bool			MOUSE_POINTER_ON = true;
const bool			USE_LOCAL_SERVER = true;
const float			MOUSE_ROTATION_SENSITIVITY = 0.1f;


// KEY MAPPING
const int			VK_W = 0x57;
const int			VK_S = 0x53;
const int			VK_1 = 0x31;
const int			VK_2 = 0x32;


// Axis Set
const D3DXVECTOR3	ZERO_VECTOR3{ 0.0f, 0.0f, 0.0f };
const D3DXVECTOR3	X_AXIS_VECTOR3{ 1.0f, 0.0f, 0.0f };
const D3DXVECTOR3	Y_AXIS_VECTOR3{ 0.0f, 1.0f, 0.0f };
const D3DXVECTOR3	Z_AXIS_VECTOR3{ 0.0f, 0.0f, 1.0f };


// Alpha Object Management
const int			ORDER_COMPASS_UI = 1;