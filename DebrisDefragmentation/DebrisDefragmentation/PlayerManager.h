#pragma once
#include "DDConfig.h"
#include "GameOption.h"
#include "Player.h"
#include "DDCamera.h"

// ���漱��
//class Player;

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	CREATE_FUNC( PlayerManager );

	bool		AddPlayer( int playerId );
	void		DeletePlayer( int playerId );
	Player*		GetPlayer( int playerId ) { return m_PlayerList[playerId]; }
			
	unsigned int GetCurrentPlayers() const { return m_CurrentPlayers; }

	DDCamera*	GetCamera() const { return m_Camera; }
	void		SetCamera( DDCamera* val ) { m_Camera = val; }

	// ī�޶� ���� ������ �������� �Լ�, yaw(y) pitch(x) roll(z)�� ������
	std::tuple<float, float, float> GetCameraViewingDirection();


private:

	// player list
	unsigned int	m_CurrentPlayers = 0;
	std::array<Player*, MAX_PLAYER_NUM> 	m_PlayerList;
	DDCamera*		m_Camera = nullptr;
	
};

extern std::shared_ptr<PlayerManager> g_PlayerManager;