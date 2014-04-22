#pragma once
#include "ClassComponent.h"
class Striker :
	public ClassComponent
{
public:
	Striker();
	virtual ~Striker();

	CREATE_FUNC( Striker );
};

