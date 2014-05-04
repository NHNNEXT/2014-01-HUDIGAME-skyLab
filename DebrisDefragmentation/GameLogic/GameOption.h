﻿#pragma once
#include <string>
#include <array>

enum class CharacterClass
{
	NO_CLASS = -1,
	STRIKER,
	ENGINEER,
	PROTECTOR
};

enum class ClientUITag
{
	UI_OXYGEN_TAG,
	UI_FUEL_TAG,
	UI_FRAME_TAG,
	UI_TAG_COUNT // total UI 숫자
};
enum class TeamColor
{
	NO_TEAM = -1,
	BLUE,
	RED
};

enum class ISSModuleName
{
	// 이름 의미있는 걸로 바꾸는 게 좋을까
	// 하지만 실제 ISS 이름은 PART1보다 더 이해하기 어려운 이름인 게 함정 ㅋㅋ
	NO_MODULE = -1,
	PART1,
	PART2,
	PART3,
	PART4,
	PART5,
	PART6,
	PART7,
	PART8
};
const unsigned int	MODULE_NUMBER = 8;

// 게임 셋팅
const unsigned int	MAX_PLAYER_NUM = 8;
const float			ACCELERATION_WEIGHT = 1.0f;
const float			COLLISION_ACCELERATION_WEIGHT = 0.5f;
const unsigned int	ACCELERATION_TIME = 500;

const int			VECTOR_DIRECTION_3 = 3;
const int			BOX_POINT_COUNT = 8;

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

#define				BLUE_TEAM_POSITION	D3DXVECTOR3(100.0f, .0f, .0f)
#define				RED_TEAM_POSITION	D3DXVECTOR3(-100.0f, .0f, .0f)
#define				BLUE_TEAM_ROTATION	D3DXVECTOR3(.0f, 270.0f, .0f)
#define				RED_TEAM_ROTATION	D3DXVECTOR3(.0f, 90.0f, .0f)




const float			CHARACTER_CB_CENTER_POS_X = 0.0f;
const float			CHARACTER_CB_CENTER_POS_Y = -0.5f;
const float			CHARACTER_CB_CENTER_POS_Z = 0.0f;

// 추진체 관련
const int			OXYGEN_COUNSUMED = 1;
const int			HEALTH_REDUCED_BY_OXYGEN_INSUFFICIENT = 10;
const int			GAS_FOR_GOFORWARD = 30;

const int			DEFAULT_OXYGEN = 200;
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
#define				ZERO_VECTOR3		D3DXVECTOR3( 0.0f, 0.0f, 0.0f )
#define				X_AXIS_VECTOR3		D3DXVECTOR3( 1.0f, 0.0f, 0.0f )
#define				Y_AXIS_VECTOR3		D3DXVECTOR3( 0.0f, 1.0f, 0.0f )
#define				Z_AXIS_VECTOR3		D3DXVECTOR3( 0.0f, 0.0f, 1.0f )


