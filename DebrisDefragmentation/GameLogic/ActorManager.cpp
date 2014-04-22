#include "stdafx.h"
#include "ActorManager.h"


ActorManager::ActorManager()
{
	for ( unsigned int playerId = 0; playerId < MAX_PLAYER_NUM; ++playerId )
	{
		m_ActorList[playerId] = nullptr;
	}
}


ActorManager::~ActorManager()
{
}

void ActorManager::Init( )
{
	m_PrevTime = timeGetTime( );
	// InitializeSRWLock( &m_SRWLock );
}

int ActorManager::RegisterUser( Actor* newActor )
{
	// user id를 manager에 등록된 actor index와 같게 유지하면 객체들 인터랙션을 처리할 때 유리할 것 같은데
	// 어떻게 효율적으로 비어있는 index를 찾고 그걸 세션에게 할당할 지 잘 모르겠네요
	// 일단 이렇게 처음부터 순회하면서 비어있는 자리가 있으면 거기에 포인터 등록하고 idx 반환하도록 하는데...
	for ( unsigned int actorId = 0; actorId < MAX_PLAYER_NUM; ++actorId )
	{
		if ( m_ActorList[actorId] == nullptr )
		{
			m_ActorList[actorId] = newActor;
			return actorId;
		}
	}

	return -1; // 빈 자리가 없습니다.
}

void ActorManager::ChangeActor( Actor* newActor, int actorId )
{
	// 다른 세션 캐릭터를 바꾸는 일은 없도록 만들어야 할 듯
	m_ActorList[actorId] = newActor;
}

void ActorManager::DeleteActor( int actorId )
{
	if ( m_ActorList[actorId] != nullptr )
	{
		delete m_ActorList[actorId];
		m_ActorList[actorId] = nullptr;
	}
}

void ActorManager::Update( )
{
	DWORD currentTime = timeGetTime( );
	float dt = ( static_cast<float>( currentTime - m_PrevTime ) ) / 1000.f;
	m_PrevTime = currentTime;

	for ( unsigned int actorId = 0; actorId < MAX_PLAYER_NUM; ++actorId )
	{
		if ( m_ActorList[actorId] != nullptr )
		{
			m_ActorList[actorId]->Update( dt );
		}
	}

	// 충돌 체크
}

bool ActorManager::IsValidId( int actorId )
{
	if ( m_ActorList[actorId] != nullptr )
		return true;

	return false;
}