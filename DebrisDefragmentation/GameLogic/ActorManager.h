#pragma once

#include "GameConfig.h"
#include "Actor.h"

class ActorManager
{
public:
	ActorManager();
	~ActorManager();

	void Init( );

	/* 
		클라이언트 처음 접속하면 클라이언트 세션이 해당 플레이어의 액터-게임 캐릭터-를 등록한다.
		클라이언트 세션의 멤버 액터의 포인터를 인자로 넣어서 등록하고,
		매니저는 등록된 인덱스값을 actorId로 사용하도록 반환한다.
		최경욱 2014. 4. 22
	*/ 
	int		RegisterUser( Actor* newActor );

	/*
		클라이언트 세션이 선택하고 있는 캐릭터를 다른 것으로 변경(나중에 추가될 클래스 시스템에서 클래스 교체)
		새롭게 등록할 캐릭터 포인터와 id를 넘겨서 등록한다.
		최경욱 2014. 4. 22
	*/
	void	ChangeActor( Actor* newActor, int actorId );
	void	DeleteActor( int actorId );

	// 조심해!!
	// 한 번에 방송하지 말고 변화가 있는 애들만 안에서 골라서 싱크 시키자
	// update - 일단 가지고 있는 플레이어들 상태를 업데이트 한다.
	bool Update( );

	/*
		인자로 받은 id가 유효한지(list에 등록되어 있는지) 판정
		최경욱 2014. 4. 22
	*/
	bool IsValidId( int actorId );
	Actor* GetActor( int actorId ) { return m_ActorList[actorId]; }

	// get other object data
	// 지금은 없습니다.

private:
	// 지금은 싱글 스레드니까 락은 필요없다.
	// SRWLOCK m_SRWLock;

	DWORD m_PrevTime = 0;

	// player list
	std::array<Actor*, MAX_PLAYER_NUM> m_ActorList;

	bool CheckCollision();

	// other objects
	// 지금은 없음요
};

