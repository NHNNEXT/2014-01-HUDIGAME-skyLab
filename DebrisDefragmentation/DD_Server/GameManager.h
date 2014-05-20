#pragma once

#include "ActorManager.h"

class GameManager : public ActorManager
{
public:
	GameManager();
	~GameManager(); ///# 아래 오버라이딩해서 쓰고 있는데.. 팍셔미 ㄱㄱ 

	void BroadcastSkillResult( int idx, ClassSkill skillType ); ///# idx 의미가 무엇인지 바로 보이지 않는다. 네이밍 수정.
	void DoPeriodWork();

private:

};