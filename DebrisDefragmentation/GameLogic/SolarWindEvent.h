#pragma once
#include "InGameEvent.h"
class SolarWindEvent :
	public InGameEvent
{
public:
	SolarWindEvent();
	virtual ~SolarWindEvent();

	virtual void Run();
};

