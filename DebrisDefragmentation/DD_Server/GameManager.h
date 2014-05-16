#pragma once

#include "ActorManager.h"

class GameManager : public ActorManager
{
public:
	GameManager();
	~GameManager();

	void BroadcastSkillResult( int idx, ClassSkill skillType );
	void DoPeriodWork();

private:

};