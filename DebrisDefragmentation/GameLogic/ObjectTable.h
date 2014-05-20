#pragma once

#include <array>
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

	///# T는 컴파일타임에 결정되는 거고, typeid()는 런타임에 타입을 알아야할 때 쓰는거다.. 완전 오용하고 있는 경우라고 볼 수 있지..
	///# 왜 이렇게 하나의 템플릿 함수로 한 것인지?? 그냥 GetInstance한 다음에 GetTransform() 부르면 되는데.. (단계가 깊은것도 아니라서..)
	///# 정 템플릿을 쓰고 싶으면 "템플릿 특수화"를 쓰면 된다.
	template<typename T>
	T* GetInstance( int key )
	{
		void* returnPtr = nullptr;

		// typeid로 비교하면 되려나
		if ( typeid( T ) == typeid( Character ) )
			returnPtr = m_CharacterList[key];
		else if ( typeid( T ) == typeid( Transform ) )
			returnPtr = m_CharacterList[key]->GetTransform( );
		else if ( typeid( T ) == typeid( ClassComponent ) )
			returnPtr = m_CharacterList[key]->GetClassComponent();

		return static_cast<T*>( returnPtr );
	}

	ActorManager* GetActorManager() { return m_ActorManager; }

	void Init( ActorManager* actorManager );

	void SetActorManager( ActorManager* actorManager ) { m_ActorManager = actorManager; } ///# 쓰이는데가 없는디...
	void SetCharacter( Character* character, int idx ) { m_CharacterList[idx] = character; }

private:
	ActorManager*		m_ActorManager = nullptr;
	std::array<Character*, MAX_PLAYER_NUM> m_CharacterList; ///# 이거 초기화는 생성자에서 일단 해놓는게 좋다. 나중에 Init을 부를지라도...
};

extern ObjectTable* GObjectTable;