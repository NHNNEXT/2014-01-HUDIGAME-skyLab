/*
	Character를 상속받은 bot
	움직임과 각종 스킬들을 구현한다.
	세부 클래스는 하위 클래스에서 구현할 것

	봇 클래스를 캐릭터로부터 상속받아서 만들지, 
	플레이어 클래스를 컨트롤하는 봇 객체를 따로 만들지 고민 필요...

	2014. 4. 21 최경욱
*/
#pragma once

#include "Actor.h"

class Bot : public Actor
{
public:
	Bot();
	virtual ~Bot();
};

