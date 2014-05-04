/*
	ISS의 부분을 이루는 모듈들
	ISS 좌표계에서의 자신의 위치를 가지고 있다.
	파괴될 수 있고 체력을 가지고 있다
	점령될 수 있는 포인트-좌표-를 가지고 있다.
	현재 어느팀이 점령하고 있는지 저장하는 변수를 가진다.
*/

#pragma once

#include "Actor.h"
#include "ISSAccessPoint.h"

class ISSModule : public Actor
{
public:
	ISSModule();
	virtual ~ISSModule();

	void Init( ISSModuleName moduleName );
	void DecreaseHP();

private:
	virtual void UpdateItSelf( float dTime );

	ISSAccessPoint	m_AccessPoint;
	TeamColor		m_CurrentTeam = TeamColor::NO_TEAM;
	float			m_HealthPoint = 1.0f;
};

