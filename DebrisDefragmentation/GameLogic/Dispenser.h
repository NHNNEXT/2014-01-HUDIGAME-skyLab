#pragma once
#include "Actor.h"

class Dispenser : public Actor
{
public:
	Dispenser();
	virtual ~Dispenser();
	TeamColor GetTeamColor() const { return m_TeamColor; }
	void SetTeamColor( TeamColor val ) { m_TeamColor = val; }

private :
	virtual void UpdateItSelf( float dTime );	
	
	float m_Oxygen = DISPENSER_DEFAULT_OXYGEN;
	float m_Fuel = DISPENSER_DEFAULT_FUEL;
	TeamColor m_TeamColor = TeamColor::NO_TEAM;

};

