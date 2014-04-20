#pragma once

#include "DDConfig.h"
#include "Player.h"
#include "PlayScene.h"

const unsigned int MAX_PLAYER_NUM = 8;

class GameLogic
{
public:
	GameLogic();
	~GameLogic();

	void Init();

	// 로그인 하면 추가한다.
	// 성공하면 id를 준다.
		
	bool AddPlayer( int playerId );

	// 조심해!!
	// getplayer에 const 땠음.. addChild 하기위해. 캡슐화..ㅠㅠ
	// 나중에 AddPlayer안에 만들자. 
	Player*		GetPlayer( int playerId ) { return m_PlayerList[playerId]; }
	void		DeletePlayer( int playerId );

	DDScene*	CreateScene( std::wstring sceneName );
	DDScene*	GetScene() const { return m_Scene; }	
	
	//	update - 일단 가지고 있는 플레이어들 상태를 업데이트 한다.
	void Update();

	// 특정 플레이어에 대해서 업데이트 한다.
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
	bool RotateDicrection( unsigned int playerId, float x, float y );

	// get Player data
	DDVECTOR3 GetPosition( unsigned int playerId );
	DDVECTOR3 GetScale( unsigned int playerId );
	DDVECTOR3 GetRotation( unsigned int playerId );
	DDVECTOR3 GetVelocity( unsigned int playerId );

	// get other object data
	// 지금은 없습니다.

private:
	DWORD m_PrevTime = 0;

	// player list
	unsigned int	m_CurrentPlayers = 0;
	
	Player*			m_PlayerList[MAX_PLAYER_NUM];

	// other objects
	// scene을 추후에 list등으로 만들 수도 있겠네요
	PlayScene*		m_Scene = nullptr;
};

extern GameLogic* GGameLogic;