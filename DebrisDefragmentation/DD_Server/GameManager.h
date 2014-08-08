#pragma once

#include "ActorManager.h"

class GameManager : public ActorManager
{
public:
	GameManager();
	virtual ~GameManager();

	void BroadcastCharacterChange( int targetId, ChangeType type );

	void DoPeriodWork();
};