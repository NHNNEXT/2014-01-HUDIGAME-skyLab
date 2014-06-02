﻿#pragma once
#include "Actor.h"

class Dispenser : public Actor
{
public:
	Dispenser( unsigned int id, TeamColor color, float issPos )
		: m_DispenserId( id ), m_Team( color ), m_FirstIssPos( issPos )
	{
	}
	virtual ~Dispenser();

	// 설치
	void Install();

	void UpdateIssPosition( float pos ) { m_Matrix._43 = pos - m_FirstIssPos; }

	void SetId( unsigned int id ) { m_DispenserId = id; }

	TeamColor GetTeamColor( ) const { return m_Team; }
	void SetTeamColor( TeamColor val ) { m_Team = val; }

private :
	virtual void UpdateItSelf( float dTime );	

	TeamColor		m_Team = TeamColor::NO_TEAM;
	unsigned int	m_DispenserId = 0;
	float			m_FirstIssPos = 0.0f;
	
	float m_Oxygen = DISPENSER_DEFAULT_OXYGEN;
	float m_Fuel = DISPENSER_DEFAULT_FUEL;
};

