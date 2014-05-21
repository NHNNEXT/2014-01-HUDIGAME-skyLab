#pragma once
#include "DDModel.h"
#include "GameOption.h"
class DispenserModel :
	public DDModel
{
public:
	DispenserModel();
	virtual ~DispenserModel();

	CREATE_OBJECT( DispenserModel );

private :
	float m_Oxygen = DISPENSER_DEFAULT_OXYGEN;
	float m_Fuel = DISPENSER_DEFAULT_FUEL;
};

