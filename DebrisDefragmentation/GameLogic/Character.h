/*
	Character를 상속받은 player
	움직임과 각종 스킬들을 구현한다.
	세부 클래스는 하위 클래스에서 구현할 것
*/
#pragma once

#include "Actor.h"
#include "GameOption.h"

class Character : public Actor
{
public:
	Character( CharacterClass characterClass = CharacterClass::ENGINEER ) 
	{ 
		m_CharacterClass = ClassComponent::Create( characterClass ); 
	}
	virtual ~Character();

	void	Init();
	void	InitTeamPosition();

	ClassComponent* GetClassComponent() { return m_CharacterClass.get(); }
	void	ChangeClass( CharacterClass newClass );

	// player 상태 가져오기
	int		GetCharacterId() const { return m_CharacterId; }
	void	SetCharacterId( int characterId ) { m_CharacterId = characterId; }

private:
	virtual void UpdateItSelf( float dTime );

	std::shared_ptr<ClassComponent> m_CharacterClass;

	int m_CharacterId = -1;
};

