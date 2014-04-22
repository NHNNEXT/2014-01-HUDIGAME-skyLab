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

const int			DEFAULT_OXYGEN = 1000;
const int			DEFAULT_GAS = 1000;
const int			DEFAULT_HP = 100;
