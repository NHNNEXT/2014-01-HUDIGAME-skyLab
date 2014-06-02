#pragma once

#include "ActorManager.h"

class GameManager : public ActorManager
{
public:
	GameManager();
	virtual ~GameManager();

	///# idx 의미가 무엇인지 바로 보이지 않는다. 네이밍 수정.
	void BroadcastSkillResult( int idx, ClassSkill skillType );
	void BroadcastCharacterChange( int idx, ChangeType type );
	void BroadcastDispenserEffect( int idx, bool dispenserEffectFlag );
	void BroadcastStructureInstallation( int structureId, StructureType structureType, D3DXVECTOR3 position, D3DXVECTOR3 direction, TeamColor teamColor );
	void BroadcastStructureUninstallation( int structureId, StructureType structureType );

	void DoPeriodWork();
};