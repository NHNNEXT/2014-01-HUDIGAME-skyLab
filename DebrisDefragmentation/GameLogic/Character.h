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
		ChangeClass( characterClass );
	}
	virtual ~Character();

	void	Init();
	void	InitTeamPosition();

	ClassComponent* GetClassComponent() { return m_CharacterClass.get(); }
	void	ChangeClass( CharacterClass newClass );

	TeamColor	GetTeam() const { return m_Team; }
	void		SetTeam( TeamColor val ) { m_Team = val; }

	// player 상태 가져오기
	int		GetCharacterId() const { return m_CharacterId; }
	void	SetCharacterId( int characterId ) { m_CharacterId = characterId; }

	void	SetDeadFlag( bool flag ) { m_IsDead = flag; }
	bool	GetDeadFlag() { return m_IsDead; }

private:
	virtual void UpdateItSelf( float dTime );

	std::shared_ptr<ClassComponent> m_CharacterClass;
	TeamColor	m_Team = TeamColor::NO_TEAM;

	int			m_CharacterId = -1;
	float		m_IsDead = false;
};

