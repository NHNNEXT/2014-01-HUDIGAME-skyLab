#pragma once

#include <string>
#include <map>

// Config
#define				USE_LOCAL_SERVER
//#define				USE_CHARACTER_COLLISION_BOX
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

const float			UI_SPECIAL_KEY_POSITION_X = 36.0f;
const float			UI_SPECIAL_KEY_POSITION_Y = 340.0f;

const float			UI_ISS_NAV_DEFAULT_POSITION_X = 373.0f;
const float			UI_ISS_NAV_DEFAULT_POSITION_Y = 35.0f;

const float			UI_ISS_NAV_DEFAULT_RANGE = 330.0f;


// UI_FILENAME_LIST와 동기화시킬 것
enum class ClientUITag : int
{
	UI_TAG_FRAME,

	UI_TAG_TEAM_RED,
	UI_TAG_TEAM_BLUE,

	UI_TAG_ISS_POSITION,
	UI_TAG_DISASTER,

	UI_TAG_SK_ENGINEER,
	UI_TAG_SK_PROTECTOR,
	UI_TAG_SK_STRIKER,

	UI_TAG_MODULE_0_NO,
	UI_TAG_MODULE_0_BLUE,
	UI_TAG_MODULE_0_RED,

	UI_TAG_MODULE_1_NO,
	UI_TAG_MODULE_1_BLUE,
	UI_TAG_MODULE_1_RED,

	UI_TAG_MODULE_2_NO,
	UI_TAG_MODULE_2_BLUE,
	UI_TAG_MODULE_2_RED,

	UI_TAG_MODULE_3_NO,
	UI_TAG_MODULE_3_BLUE,
	UI_TAG_MODULE_3_RED,

	UI_TAG_MODULE_4_NO,
	UI_TAG_MODULE_4_BLUE,
	UI_TAG_MODULE_4_RED,

	UI_TAG_MODULE_5_NO,
	UI_TAG_MODULE_5_BLUE,
	UI_TAG_MODULE_5_RED,

	UI_TAG_MODULE_6_NO,
	UI_TAG_MODULE_6_BLUE,
	UI_TAG_MODULE_6_RED,

	UI_TAG_MODULE_7_NO,
	UI_TAG_MODULE_7_BLUE,
	UI_TAG_MODULE_7_RED,

	UI_TAG_MODULE_8_NO,
	UI_TAG_MODULE_8_BLUE,
	UI_TAG_MODULE_8_RED,

	UI_TAG_MODULE_9_NO,
	UI_TAG_MODULE_9_BLUE,
	UI_TAG_MODULE_9_RED,
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
	{ ClientUITag::UI_TAG_FRAME, L"screen_component\\frame.png" },
	{ ClientUITag::UI_TAG_TEAM_RED, L"screen_component\\team_red.png" },
	{ ClientUITag::UI_TAG_TEAM_BLUE, L"screen_component\\team_blue.png" },
	{ ClientUITag::UI_TAG_ISS_POSITION, L"screen_component\\iss_position.png" },
	{ ClientUITag::UI_TAG_DISASTER, L"screen_component\\disaster.png" },
	{ ClientUITag::UI_TAG_SK_ENGINEER, L"screen_component\\sk_engineer.png" },
	{ ClientUITag::UI_TAG_SK_PROTECTOR, L"screen_component\\sk_protector.png" },
	{ ClientUITag::UI_TAG_SK_STRIKER, L"screen_component\\sk_striker.png" },
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

// character animation
const float ANIM_TIME_ATTACK = 1.83f;
const float ANIM_TIME_DEAD = 1.63f;
const float ANIM_TIME_FIRE = 0.96f;
const float ANIM_TIME_IDLE = 4.0f;
const float ANIM_TIME_REACT = 5.43f;

enum class CharacterAnimState : int
{
	NO_STATE = -1,

	ATTACK,
	DEAD,
	FIRE,
	IDLE,
	REACT,
};