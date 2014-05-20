#pragma once

#include <string>
#include <array>
#include <d3dx9.h>
#include <map>

const int			VECTOR_DIRECTION_3 = 3;
const int			BOX_POINT_COUNT = 8;


// UI
const float			UI_OXYGEN_POSITION_X = 10.0f;
const float			UI_OXYGEN_POSITION_Y = 10.0f;
const float			UI_FUEL_POSITION_X = 10.0f;
const float			UI_FUEL_POSITION_Y = 30.0f;
const float			UI_FRAME_POSITION_X = 0.0f;
const float			UI_FRAME_POSITION_Y = 50.0f;


// UI_FILENAME_LIST와 동기화시킬 것
enum class ClientUITag : int
{
	UI_OXYGEN_TAG,
	UI_FUEL_TAG,
	UI_FRAME_TAG,
	UI_TAG_COUNT // total UI 숫자
};

const std::wstring	UI_FILE_PATH = L".\\Resources\\Image\\";

// ClientUITag와 동기화시킬 것
// agebreak : 위의 내용을 아래와 같이 바꾸면 대재앙을 막을수 있다! // 그렇군요!
const std::map<ClientUITag, std::wstring> MAP_UI_FILENAME =
{
	{ ClientUITag::UI_OXYGEN_TAG, L"OxygenUI.png" },
	{ ClientUITag::UI_FUEL_TAG, L"FuelUI.png" },
	{ ClientUITag::UI_FRAME_TAG, L"Frame.png" }
};

// Config
#define				USE_LOCAL_SERVER
#define				USE_CHARACTER_COLLISION_BOX
const bool			MOUSE_POINTER_ON = true;
const float			MOUSE_ROTATION_SENSITIVITY = 0.1f;


// KEY MAPPING
const int			VK_W = 0x57;
const int			VK_S = 0x53;
const int			VK_1 = 0x31;
const int			VK_2 = 0x32;
const int			VK_3 = 0x33;
const int			VK_4 = 0x34;
const int			VK_5 = 0x35;

// Axis Set
const D3DXVECTOR3	ZERO_VECTOR3{ 0.0f, 0.0f, 0.0f };
const D3DXVECTOR3	X_AXIS_VECTOR3{ 1.0f, 0.0f, 0.0f };
const D3DXVECTOR3	Y_AXIS_VECTOR3{ 0.0f, 1.0f, 0.0f };
const D3DXVECTOR3	Z_AXIS_VECTOR3{ 0.0f, 0.0f, 1.0f };


// Alpha Object Management
const int			ORDER_COMPASS_UI = 1;




// 주의! 아래쪽의 JSON_KEY_LIST와 순서를 동기화시켜야 합니다
// 주의! Tool 에서 사용하는 JsonKeyValues와 동기화시켜야 합니다
enum JsonKeyValues : int
{
	JSON_DEBRIS_NUMBER = 0,
	JSON_ISS,
	JSON_TOTAL_KEY_COUNT
};

// 주의! JsonKeyVales를 바꾸면 이쪽도 같이 바꾸자
const std::map<JsonKeyValues, std::string> JSON_KEY_MAP =
{
	{ JsonKeyValues::JSON_DEBRIS_NUMBER, "debrisNumber" },
	{ JsonKeyValues::JSON_ISS, "ISS" },
};
