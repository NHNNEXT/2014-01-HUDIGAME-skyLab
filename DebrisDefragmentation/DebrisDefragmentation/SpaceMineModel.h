#pragma once

#include "DDModel.h"
#include "GameOption.h"

class SpaceMineModel :
	public DDModel
{
public:
	SpaceMineModel();
	virtual ~SpaceMineModel();

	CREATE_OBJECT( SpaceMineModel );

	void Init( unsigned int id, TeamColor color, float issPos );

	void UpdateIssPosition( float pos ) { m_Matrix._43 = pos - m_FirstIssPos; }

private:
	unsigned int m_Id = 0;
	TeamColor m_TeamColor = TeamColor::NO_TEAM;

	float			m_FirstIssPos = 0.0f;
};

