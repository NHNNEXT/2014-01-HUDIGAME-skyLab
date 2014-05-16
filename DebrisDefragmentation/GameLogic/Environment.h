#pragma once

#include <string>
#include <array>
#include <d3dx9.h>
#include "..\GameTool\Class\jsonEnum.cs"

const int			VECTOR_DIRECTION_3 = 3;
const int			BOX_POINT_COUNT = 8;


// UI
const float			UI_OXYGEN_POSITION_X = 10.0f;
const float			UI_OXYGEN_POSITION_Y = 10.0f;
const float			UI_FUEL_POSITION_X = 10.0f;
const float			UI_FUEL_POSITION_Y = 30.0f;
const float			UI_FRAME_POSITION_X = 0.0f;
const float			UI_FRAME_POSITION_Y = 50.0f;


// 주의 : 순서를 함부로 바꾸지 말 것. 대재앙이 일어난다
// UI_FILENAME_LIST와 함께 바꿀 것
enum class ClientUITag : int
{
	UI_OXYGEN_TAG,
	UI_FUEL_TAG,
	UI_FRAME_TAG,
	UI_TAG_COUNT // total UI 숫자
};

const std::wstring	UI_FILE_PATH = L".\\Resources\\Image\\";
// 주의 : 순서를 함부로 바꾸지 말 것. 대재앙이 일어난다.
// ClientUITag와 함께 바꿀 것
const std::array<std::wstring, size_t( ClientUITag::UI_TAG_COUNT )> UI_FILENAME_LIST
= {
	L"OxygenUI.png",
	L"FuelUI.png",
	L"Frame.png"
};


// Config
#define				USE_LOCAL_SERVER
#define				USE_CHARACTER_COLLISION_BOX
const bool			MOUSE_POINTER_ON = false;
const float			MOUSE_ROTATION_SENSITIVITY = 0.1f;


// KEY MAPPING
const int			VK_W = 0x57;
const int			VK_S = 0x53;
const int			VK_1 = 0x31;
const int			VK_2 = 0x32;
const int			VK_3 = 0x33;
const int			VK_4 = 0x34;

// Axis Set
const D3DXVECTOR3	ZERO_VECTOR3{ 0.0f, 0.0f, 0.0f };
const D3DXVECTOR3	X_AXIS_VECTOR3{ 1.0f, 0.0f, 0.0f };
const D3DXVECTOR3	Y_AXIS_VECTOR3{ 0.0f, 1.0f, 0.0f };
const D3DXVECTOR3	Z_AXIS_VECTOR3{ 0.0f, 0.0f, 1.0f };


// Alpha Object Management
const int			ORDER_COMPASS_UI = 1;

// JSON key 값은 여기서만 바꿉니다
const std::array<std::string, size_t( JsonKeyValues::JSON_TOTAL_KEY_COUNT )> JSON_KEY_LIST
= {
	"debrisNumber"
};

// 복잡한 JSON 키 값 한 번에 뽑아오세요
static const char* GetJsonKeyFromList( JsonKeyValues keyNumber ) { return JSON_KEY_LIST[(int)keyNumber].c_str(); }