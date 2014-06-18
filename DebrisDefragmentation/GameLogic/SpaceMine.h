#pragma once

#include "Actor.h"

class SpaceMine : public Actor
{
public:
	SpaceMine( unsigned int id, TeamColor color, float issPos ) 
		: m_MineId( id ), m_Team( color ), m_FirstIssPos( issPos )
	{
	}
	
	virtual ~SpaceMine();

	// 설치
	void Install();

	// 발동?!
	bool React();

	void UpdateIssPosition( float pos ) { m_Matrix._43 = pos - m_FirstIssPos; }

	void SetId( unsigned int id ) { m_MineId = id; }
	unsigned int GetId() const { return m_MineId; }

	TeamColor GetTeamColor() const { return m_Team; }
	void SetTeamColor( TeamColor val ) { m_Team = val; }

private:
	TeamColor		m_Team = TeamColor::NO_TEAM;
	unsigned int	m_MineId = 0;
	float			m_FirstIssPos = 0.0f;
};

