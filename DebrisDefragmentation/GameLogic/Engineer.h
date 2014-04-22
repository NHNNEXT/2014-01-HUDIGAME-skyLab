#pragma once
#include "ClassComponent.h"
class Engineer :
	public ClassComponent
{
public:
	Engineer();
	virtual ~Engineer();

	CREATE_FUNC( Engineer );
};

