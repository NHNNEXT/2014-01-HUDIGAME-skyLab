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
	void SetHP( float hp ) { m_HealthPoint = hp; }
	float GetHP() const { return m_HealthPoint; }
	const CollisionBox* GetControlPointBox();

	void SetISSPos( float pos ) { m_ISSPos = pos; }

	TeamColor Occupy( TeamColor callerColor );
	TeamColor GetOwner() const { return m_CurrentOwner; }
	void SetOwner( TeamColor color ) { m_CurrentOwner = color; }
	ISSModuleName GetModuleName() const { return m_ModuleName; }

private:
	virtual void UpdateItSelf( float dTime );

	ISSModuleName	m_ModuleName = ISSModuleName::NO_MODULE;
	TeamColor		m_CurrentOwner = TeamColor::NO_TEAM;
	float			m_ISSPos = 0.0f;
	float			m_HealthPoint = 1.0f;

	// control point를 그냥 충돌 박스 형태로만 가지고 있어도 될 것 같은데
	// 그런데 이것도 기본값 + 변환 적용 버전 2개로 만들어야 하나
	// 어차피 GetCollisionBox()할 때 변환 적용해서 반환하니까
	// 변환 결과가 저장되는 변수는 공유할 수 있을 듯
	CollisionBox	m_ControlBox;
};

