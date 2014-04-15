#pragma once

#include "DDConfig.h"
#include "Player.h"
#include "DDScene.h"

const unsigned int MAX_PLAYER_NUM = 8;

class GameLogic
{
public:
	GameLogic();
	~GameLogic();

	void Init();

	// �α��� �ϸ� �߰��Ѵ�.
	// �����ϸ� id�� �ش�.
		
	bool AddPlayer( int playerId );

	// ������!!
	// getplayer�� const ����.. addChild �ϱ�����. ĸ��ȭ..�Ф�
	// ���߿� AddPlayer�ȿ� ������. 
	Player*	GetPlayer( int playerId ) { return m_PlayerList[playerId]; }
	void			DeletePlayer( int playerId );

	void		CreateScene();
	DDScene*	GetScene() const { return m_Scene; }	
	
	//	update - �ϴ� ������ �ִ� �÷��̾�� ���¸� ������Ʈ �Ѵ�.
	void Update();

	// Ư�� �÷��̾ ���ؼ� ������Ʈ �Ѵ�.
	void UpdatePlayerMove( int playerId, DDVECTOR3 pos, DDVECTOR3 vel, DDVECTOR3 rot );
	void UpdatePlayerStop( int playerId, DDVECTOR3 pos );
	void UpdatePlayerRotation( int playerId, DDVECTOR3 rot );
	void UpdatePlayerSync( int playerId, DDVECTOR3 pos, DDVECTOR3 vel, DDVECTOR3 rot );
	void UpdatePlayerNew( int playerId, DDVECTOR3 pos, DDVECTOR3 vel, DDVECTOR3 acc, DDVECTOR3 rot );

	unsigned int GetCurrentPlayers() const { return m_CurrentPlayers; }	
// 	void IncreaseCurrentPlayers() { ++m_CurrentPlayers; }
// 	void DecreaseCurrentPlayers() { --m_CurrentPlayers; }


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
	// ������ �����ϴ�.

private:
	DWORD m_PrevTime = 0;

	// player list
	unsigned int	m_CurrentPlayers = 0;
	Player*			m_PlayerList[MAX_PLAYER_NUM];

	// other objects
	// scene�� ���Ŀ� list������ ���� ���� �ְڳ׿�
	DDScene* m_Scene = nullptr;
};

extern GameLogic* GGameLogic;