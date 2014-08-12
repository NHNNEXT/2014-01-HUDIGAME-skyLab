#pragma once

#include "GameOption.h"

class DebrisZone;
class Debris;

class DebrisManager
{
public:
	DebrisManager();
	~DebrisManager();

	void Init();

	// 충돌 체크와 데브리들의 이동을 진행
	void Update( float dt );

	void ChangeDebrisZone( Debris* debris, int prevZone, int newZone );

private:
	std::array<DebrisZone*, DEBRIS_ZONE_NUMBER> m_DebrisZoneList;
};

extern DebrisManager* GDebrisManager;