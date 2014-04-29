#pragma once

const unsigned int	MAX_PLAYER_NUM = 8;
const float			ACCELERATION_WEIGHT = 1.0f;
const float			COLLISION_ACCELERATION_WEIGHT = 0.5f;
const unsigned int	ACCELERATION_TIME = 500;
const float			MOUSE_ROTATION_WEIGHT = 0.1f;

const int			VECTOR_DIRECTION_3 = 3;
const int			BOX_POINT_COUNT = 8;

const float			CHARACTER_CB_LENGTH_X = 1.0f;
const float			CHARACTER_CB_LENGTH_Y = 1.0f;
const float			CHARACTER_CB_LENGTH_Z = 1.0f;

const float			CHARACTER_CB_CENTER_POS_X = 0.0f;
const float			CHARACTER_CB_CENTER_POS_Y = 0.0f;
const float			CHARACTER_CB_CENTER_POS_Z = 0.0f;

// 추진체 관련
const int			OXYGEN_COUNSUMED = 1;
const int			HEALTH_REDUCED_BY_OXYGEN_LEAKAGE = 10;
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
const float			UI_FRAME_POSITION_Y = 30.0f;

// setting
const bool			MOUSE_POINTER_ON = true;
const float			BLUE_TEAM_POS = 200.0f;
const float			RED_TEAM_POS = -200.0f;

#define				ZERO_VECTOR3		D3DXVECTOR3( 0.0f, 0.0f, 0.0f )
#define				X_AXIS_VECTOR3		D3DXVECTOR3( 1.0f, 0.0f, 0.0f )
#define				Y_AXIS_VECTOR3		D3DXVECTOR3( 0.0f, 1.0f, 0.0f )
#define				Z_AXIS_VECTOR3		D3DXVECTOR3( 0.0f, 0.0f, 1.0f )