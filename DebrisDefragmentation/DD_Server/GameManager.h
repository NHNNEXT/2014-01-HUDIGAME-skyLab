#pragma once

#include "ActorManager.h"

class GameManager : public ActorManager
{
public:
	GameManager();
	virtual ~GameManager();

	void BroadcastCharacterChange( int targetId, ChangeType type );
	void BroadcastIssChange();

	void BroadcastDispenserEffect( int idx, bool dispenserEffectFlag );

	void BroadcastStructureInstallation( int structureId, StructureType structureType, D3DXVECTOR3 position, D3DXVECTOR3 direction, TeamColor teamColor );
	void BroadcastStructureUninstallation( int structureId, StructureType structureType );

	void BroadcastDisasterOccurrence(D3DXVECTOR3 direction, float remainTime);	
	void BroadcastISSSkillResult( D3DXVECTOR3 direction, D3DXVECTOR3 position );

	void DoPeriodWork();
};