#pragma once

#include "GameOption.h"
#include "Character.h"

class ActorManager;

class ObjectTable
{
public:
	ObjectTable( ) {}
	~ObjectTable();

	/*
		인덱스와 타입을 인자로 받아서 해당하는 액터의 포인터를 반환
		인자로 받을 수 있는 타입은 Actor, Transform, ClassComponent
	*/
	template<typename T>
	T* GetInstance( int key )
	{
		if ( m_CharacterList[key] == nullptr )
			return nullptr;

		void* returnPtr = nullptr;

		// typeid로 비교하면 되려나
		if ( typeid( T ) == typeid( Character ) )
			returnPtr = m_CharacterList[key];
		else if ( typeid( T ) == typeid( Transform ) )
			returnPtr = m_CharacterList[key]->GetTransform( );
		else if ( typeid( T ) == typeid( ClassComponent ) )
			returnPtr = m_CharacterList[key]->GetClassComponent();
		else if ( typeid( T ) == typeid( Rigidbody ) )
			returnPtr = m_CharacterList[key]->GetRigidbody();

		return static_cast<T*>( returnPtr );
	}

	ActorManager* GetActorManager() { return m_ActorManager; }

	void Init( ActorManager* actorManager );

	void SetActorManager( ActorManager* actorManager ) { m_ActorManager = actorManager; }
	void SetCharacter( Character* character, int idx ) { m_CharacterList[idx] = character; }

private:
	ActorManager*		m_ActorManager = nullptr;
	std::array<Character*, MAX_PLAYER_NUM> m_CharacterList;
};

extern ObjectTable* GObjectTable;