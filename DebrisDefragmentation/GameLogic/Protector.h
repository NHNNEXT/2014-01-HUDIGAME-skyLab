#pragma once
#include "ClassComponent.h"
class Protector :
	public ClassComponent
{
public:
	Protector();
	virtual ~Protector();

	CREATE_FUNC( Protector );
};

