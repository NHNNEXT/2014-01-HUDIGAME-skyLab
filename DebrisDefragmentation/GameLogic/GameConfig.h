#pragma once

#include "stdafx.h"

const unsigned int MAX_PLAYER_NUM = 8;


#define CREATE_FUNC(CLASS_NAME) \
	static std::shared_ptr<CLASS_NAME> Create() \
{ \
	std::shared_ptr<CLASS_NAME> pInstance(new CLASS_NAME()); \
	return pInstance; \
}