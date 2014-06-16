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
