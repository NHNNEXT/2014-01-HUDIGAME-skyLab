#pragma once
#include "DDModel.h"
#include "GameOption.h"
class DispenserModel :
	public DDModel
{
public:
	DispenserModel( unsigned int id, TeamColor color, float issPos )
		: m_Id( id ), m_TeamColor( color ), m_FirstIssPos( issPos )
	{
	}
	virtual ~DispenserModel();

	void UpdateIssPosition( float pos ) { m_Matrix._43 = pos - m_FirstIssPos; }

private :
	unsigned int m_Id = 0;
	TeamColor m_TeamColor = TeamColor::NO_TEAM;

	float			m_FirstIssPos = 0.0f;

	float m_Oxygen = DISPENSER_DEFAULT_OXYGEN;
	float m_Fuel = DISPENSER_DEFAULT_FUEL;
};

