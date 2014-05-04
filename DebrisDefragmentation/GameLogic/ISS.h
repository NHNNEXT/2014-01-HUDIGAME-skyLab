/*
	ISS자체
	자신을 이루는 모듈들을 arrary로 가지고 있다.
	주기적으로 각각의 모듈을 점령하고 있는 팀의 수에 따라서 움직인다.
*/

#pragma once

#include "Actor.h"
#include "ISSModule.h"

class ISS : public Actor
{
public:
	ISS();
	virtual ~ISS();

	void Init();

	ISSModuleName						Occupy( int skillUserId );
	std::tuple<ISSModuleName, float>	Destroy( int skillUserId );

private:
	virtual void UpdateItSelf( float dTime );

	std::array<ISSModule, MODULE_NUMBER> m_ModuleList;
};
