#pragma once

#include "GameConfig.h"
#include "PlayerCharacter.h"

class GameLogic
{
public:
	GameLogic();
	~GameLogic();

	void Init();

	// 로그인 하면 추가한다.
	// 성공하면 id를 준다.
	int AddPlayer();
	
	void DeletePlayer( int playerId );

	// update - 일단 가지고 있는 플레이어들 상태를 업데이트 한다.
	void Update();

	bool IsValidId( int playerId );

	// set Player data
	bool SetPosition( unsigned int playerId, float x, float y, float z );
	bool SetScale( unsigned int playerId, float scaleX, float scaleY, float scaleZ );
	bool SetRotation( unsigned int playerId, float rotationX, float rotationY, float rotationZ );

	bool SetAcceleration( unsigned int playerId );
	bool Stop( unsigned int playerId );
	bool RotateDicrection( unsigned int playerId, float y, float x );

	// get Player data
	DDVECTOR3 GetPosition( unsigned int playerId );
	DDVECTOR3 GetScale( unsigned int playerId );
	DDVECTOR3 GetRotation( unsigned int playerId );
	DDVECTOR3 GetVelocity( unsigned int playerId );

	// get other object data
	// 지금은 없습니다.

private:
	// 지금은 싱글 스레드니까 락은 필요없다.
	// SRWLOCK m_SRWLock;

	DWORD m_PrevTime = 0;

	// player list
	PlayerCharacter* m_PlayerList[MAX_PLAYER_NUM];

	// other objects
	// 지금은 없음요
};

extern GameLogic* GGameLogic;