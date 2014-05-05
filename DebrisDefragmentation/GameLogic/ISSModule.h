/*
	ISS의 부분을 이루는 모듈들
	ISS 좌표계에서의 자신의 위치를 가지고 있다.
	파괴될 수 있고 체력을 가지고 있다
	점령될 수 있는 포인트-좌표-를 가지고 있다.
	현재 어느팀이 점령하고 있는지 저장하는 변수를 가진다.

	ISS의 m_Matrix를 반영하는 코드 필요
*/

#pragma once

#include "Actor.h"
#include "ISSControlPoint.h"

class ISSModule : public Actor
{
public:
	ISSModule();
	virtual ~ISSModule();

	void Init( ISSModuleName moduleName );
	float DecreaseHP();
	const CollisionBox* GetControlPointBox();

	TeamColor Occupy( TeamColor callerColor );
	TeamColor GetOwner() const { return m_CurrentOwner; }
	ISSModuleName GetModuleName() const { return m_ModuleName; }

private:
	virtual void UpdateItSelf( float dTime );

	ISSControlPoint	m_ControlPoint;
	ISSModuleName	m_ModuleName = ISSModuleName::NO_MODULE;
	TeamColor		m_CurrentOwner = TeamColor::NO_TEAM;
	float			m_HealthPoint = 1.0f;
};

