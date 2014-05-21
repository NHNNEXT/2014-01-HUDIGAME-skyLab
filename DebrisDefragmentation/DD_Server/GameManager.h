#pragma once

#include "ActorManager.h"

class GameManager : public ActorManager
{
public:
	GameManager();
	~GameManager();

	void BroadcastSkillResult( int idx, ClassSkill skillType );
	void BroadcastCharacterChange( int idx, ChangeType type );

	void DoPeriodWork();

};