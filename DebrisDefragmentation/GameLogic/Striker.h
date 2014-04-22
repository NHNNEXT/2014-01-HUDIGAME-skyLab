#pragma once
#include "Avatar.h"
class Striker :
	public Avatar
{
public:
	Striker();
	virtual ~Striker();

	///# 템플릿으로 안하고 매크로로 한 이유는?
	CREATE_FUNC( Striker );
};

