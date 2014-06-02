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

	void Init( unsigned int id, TeamColor color, float issPos );

	void UpdateIssPosition( float pos ) { m_Matrix._43 = pos - m_FirstIssPos; }

private :
	unsigned int m_Id = 0;
	TeamColor m_TeamColor = TeamColor::NO_TEAM;

	float			m_FirstIssPos = 0.0f;

	float m_Oxygen = DISPENSER_DEFAULT_OXYGEN;
	float m_Fuel = DISPENSER_DEFAULT_FUEL;
};

