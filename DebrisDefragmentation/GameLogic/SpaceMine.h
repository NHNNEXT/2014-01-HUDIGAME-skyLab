#pragma once

#include "Actor.h"

class SpaceMine : public Actor
{
public:
	SpaceMine();
	virtual ~SpaceMine();

	// 설치
	void Install();

	// 가까운 위치에 
	bool React();

private:
	TeamColor m_Team = TeamColor::NO_TEAM;
};

