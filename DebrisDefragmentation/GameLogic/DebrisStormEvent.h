#pragma once

#include "InGameEvent.h"

class DebrisStormEvent :
	public InGameEvent
{
public:
	DebrisStormEvent();
	virtual ~DebrisStormEvent();

	virtual void Run();
};

