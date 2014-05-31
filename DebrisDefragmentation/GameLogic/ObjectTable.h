#pragma once

#include "GameOption.h"
#include "Character.h"

class ActorManager;

class ObjectTable
{
public:
	ObjectTable( ) 
	{
		m_CharacterList.fill( nullptr );
	}
	~ObjectTable();

	/*
		인덱스와 타입을 인자로 받아서 해당하는 액터의 포인터를 반환
		인자로 받을 수 있는 타입은 Actor, Transform, ClassComponent
	///# 정 템플릿을 쓰고 싶으면 "템플릿 특수화"를 쓰면 된다.
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
	*/

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