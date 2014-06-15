#pragma once

#include <string>
#include <map>

// Config
#define				USE_LOCAL_SERVER
#define				USE_CHARACTER_COLLISION_BOX
const bool			MOUSE_POINTER_ON = true;
const float			MOUSE_ROTATION_SENSITIVITY = 0.1f;

// UI
const float			UI_OXYGEN_POSITION_X = 10.0f;
const float			UI_OXYGEN_POSITION_Y = 10.0f;
const float			UI_FUEL_POSITION_X = 10.0f;
const float			UI_FUEL_POSITION_Y = 30.0f;
const float			UI_FRAME_POSITION_X = 0.0f;
const float			UI_FRAME_POSITION_Y = 50.0f;

const float			UI_SKELETON_POSITION_X = 15.0f;
const float			UI_SKELETON_POSITION_Y = 58.0;


// UI_FILENAME_LIST와 동기화시킬 것
enum class ClientUITag : int
{
	UI_FRAME_TAG,
	UI_OXYGEN_TAG,
	UI_FUEL_TAG,

	UI_SKELETON_FRAME,
	UI_SKELETON_CHARACTER_INFO,
	UI_SKELETON_ISS,
	UI_SKELETON_NAVIGATOR,
	UI_SKELETON_DISASTER,
	UI_SKELETON_TEAM,

	UI_TAG_COUNT // total UI 숫자
};

enum class ClientLightTag : int
{
	DIRECTIONAL_MAIN,
	LIGHT_TAG_COUNT // total LIGHT 숫자
};

const std::wstring	UI_FILE_PATH = L".\\Resources\\Image\\";

// ClientUITag와 동기화시킬 것
// agebreak : 위의 내용을 아래와 같이 바꾸면 대재앙을 막을수 있다! // 그렇군요!
const std::map<ClientUITag, std::wstring> MAP_UI_FILENAME =
{
	{ ClientUITag::UI_FRAME_TAG, L"Frame.png" },
	{ ClientUITag::UI_OXYGEN_TAG, L"OxygenUI.png" },
	{ ClientUITag::UI_FUEL_TAG, L"FuelUI.png" },
	{ ClientUITag::UI_SKELETON_FRAME, L"frame_.png" },
	{ ClientUITag::UI_SKELETON_CHARACTER_INFO, L"character_.png" },
	{ ClientUITag::UI_SKELETON_ISS, L"ISS_.png" },
	{ ClientUITag::UI_SKELETON_NAVIGATOR, L"navigator_.png" },
	{ ClientUITag::UI_SKELETON_DISASTER, L"disaster_.png" },
	{ ClientUITag::UI_SKELETON_TEAM, L"team_.png" },
};



// KEY MAPPING
const int			VK_W = 0x57;
const int			VK_S = 0x53;
const int			VK_1 = 0x31;
const int			VK_2 = 0x32;
const int			VK_3 = 0x33;
const int			VK_4 = 0x34;
const int			VK_5 = 0x35;
const int			VK_6 = 0x36;



// Alpha Object Management
const int			ORDER_COMPASS_UI = 1;

const int			BILLBOARD_RESOLUTION = 20;

enum class UIModuleTag : int
{
	NO_MODULE = -1,

	BACKGROUND_FRAME,
	CHARACTER_INFO,
	SKILL_INFO,
	NAVIGATOR,
	ISS_INFO,
	TEAM_INFO,
};