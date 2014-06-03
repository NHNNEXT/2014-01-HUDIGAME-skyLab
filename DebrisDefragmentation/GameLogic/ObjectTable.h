#pragma once

#include "GameOption.h"
#include "Character.h"

class ActorManager;

class ObjectTable ///# 모호하다.. 현재는 그냥 캐릭터 테이블 같은데?
{
public:
	ObjectTable( ) 
	{
		m_CharacterList.fill( nullptr );
	}
	~ObjectTable();

	// character 포인터만 받아서 Transform, ClassComponent, Rigidbody에 직접 접근하자
	Character* GetCharacter( int characterIdx )
	{
		return m_CharacterList[characterIdx];
	}

	ActorManager* GetActorManager() { return m_ActorManager; }

	void Init( ActorManager* actorManager );

	void SetCharacter( Character* character, int idx ) { m_CharacterList[idx] = character; }

private:
	ActorManager*		m_ActorManager = nullptr;
	std::array<Character*, REAL_PLAYER_NUM> m_CharacterList;
};

extern ObjectTable* GObjectTable;