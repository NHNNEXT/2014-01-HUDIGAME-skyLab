#pragma once
#include "Avatar.h"
class Engineer :
	public Avatar
{
public:
	Engineer();
	virtual ~Engineer();

	CREATE_FUNC( Engineer );
};

