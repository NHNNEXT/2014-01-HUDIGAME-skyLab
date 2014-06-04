#pragma once
#include "DDConfig.h"
#include "GameOption.h"
#include "Player.h"
//#include "DDCamera.h"

// 전방선언
//class Player;
class DDCamera;

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	CREATE_FUNC( PlayerManager );

	bool		AddPlayer( int playerId );
	void		DeletePlayer( int playerId );
	Player*		GetPlayer( int playerId ) { return m_PlayerList[playerId]; }
	Player*		GetMyPlayer();

	void		SetMyPlayerId( int id ) { m_MyPlayerId = id; }
			
	unsigned int GetNumberOfCurrentPlayers() const { return m_CurrentPlayers; }

	DDCamera*	GetCamera() const { return m_Camera; }
	void		SetCamera( DDCamera* val ) { m_Camera = val; }

	// 카메라 플레이어 분리 후 사용 안하여 주석처리함
	// 카메라 시점 방향을 가져오는 함수, yaw(y) pitch(x) roll(z)로 가져옴
	// D3DXVECTOR3 GetCameraViewingDirection();


private:
	// player list
	unsigned int	m_CurrentPlayers = 0;
	std::array<Player*, MAX_PLAYER_NUM> 	m_PlayerList;
	DDCamera*		m_Camera = nullptr;
	
	int				m_MyPlayerId = -1;
};

extern std::shared_ptr<PlayerManager> GPlayerManager;