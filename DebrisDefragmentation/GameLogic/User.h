﻿/*
	Character를 상속받은 player
	움직임과 각종 스킬들을 구현한다.
	세부 클래스는 하위 클래스에서 구현할 것
	2014. 4. 21 최경욱
*/
#pragma once

#include "Actor.h"

class User : public Actor
{
public:
	User( int playerId ) : m_PlayerId( playerId ) {}
	~User(); ///# 당연히 virtual!
	
	// 조심해!!
	// 이 함수 좀 이상하다...기존 함수 활용해서 사용하도록 수정할 것
	void RotateDicrection( float y, float x );

	// player 상태 가져오기
	int GetPlayerId() { return m_PlayerId; }

private:
	virtual void UpdateItSelf( float dTime );

	int				m_PlayerId = -1;
};

