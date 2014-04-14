#pragma once

#include "GameConfig.h"
#include "PlayerCharacter.h"

class GameLogic
{
public:
	GameLogic();
	~GameLogic();

	void Init();

	// �α��� �ϸ� �߰��Ѵ�.
	// �����ϸ� id�� �ش�.
	int AddPlayer();
	
	void DeletePlayer( int playerId );

	// update - �ϴ� ������ �ִ� �÷��̾�� ���¸� ������Ʈ �Ѵ�.
	void Update();

	// set Player data
	void SetPosition( unsigned int playerId, float x, float y, float z );
	void SetScale( unsigned int playerId, float scaleX, float scaleY, float scaleZ );
	void SetRotation( unsigned int playerId, float rotationX, float rotationY, float rotationZ );

	void SetAcceleration( unsigned int playerId );
	void Stop( unsigned int playerId );
	void RotateDicrection( unsigned int playerId, float y, float x );

	// get Player data
	DDVECTOR3 GetPosition( unsigned int playerId );
	DDVECTOR3 GetScale( unsigned int playerId );
	DDVECTOR3 GetRotation( unsigned int playerId );

	// get other object data
	// ������ �����ϴ�.

private:
	// ������ �̱� ������ϱ� ���� �ʿ����.
	// SRWLOCK m_SRWLock;

	DWORD m_PrevTime = 0;

	// player list
	PlayerCharacter* m_PlayerList[MAX_PLAYER_NUM];

	// other objects
	// ������ ������
};

extern GameLogic* GGameLogic;