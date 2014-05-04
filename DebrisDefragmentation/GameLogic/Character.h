﻿/*
	Character를 상속받은 player
	움직임과 각종 스킬들을 구현한다.
	세부 클래스는 하위 클래스에서 구현할 것
	2014. 4. 21 최경욱
*/
#pragma once

#include "Actor.h"
#include "GameOption.h"

class Character : public Actor
{
public:
	Character() {}
	virtual ~Character();

	void	Init();
	void	ChangeClass( CharacterClass newClass );

	// player 상태 가져오기
	int		GetCharacterId() { return m_CharacterId; }
	void	SetCharacterId( int characterId ) { m_CharacterId = characterId; }

	

private:
	virtual void UpdateItSelf( float dTime );

	int				m_CharacterId = -1;
	ClassComponent*	m_ClassCompnent = nullptr;
};

