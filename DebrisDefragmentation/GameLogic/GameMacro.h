#pragma once

#include <memory>
#include <map>
#include <d3dx9.h>

#define CREATE_FUNC(CLASS_NAME) \
	static std::shared_ptr<CLASS_NAME> Create() \
{ \
	std::shared_ptr<CLASS_NAME> pInstance(new CLASS_NAME()); \
	return pInstance; \
}

// bounding box constants
const int			VECTOR_DIRECTION_3 = 3;
const int			BOX_POINT_COUNT = 8;

// Axis Set
const D3DXVECTOR3	ZERO_VECTOR3{ 0.0f, 0.0f, 0.0f };
const D3DXVECTOR3	X_AXIS_VECTOR3{ 1.0f, 0.0f, 0.0f };
const D3DXVECTOR3	Y_AXIS_VECTOR3{ 0.0f, 1.0f, 0.0f };
const D3DXVECTOR3	Z_AXIS_VECTOR3{ 0.0f, 0.0f, 1.0f };

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