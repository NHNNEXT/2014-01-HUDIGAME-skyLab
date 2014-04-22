#pragma once
#include "DDConfig.h"
#include "GameOption.h"
#include "Player.h"

// 전방선언
class Player;

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	CREATE_FUNC( PlayerManager );

	bool		AddPlayer( int playerId );
	void		DeletePlayer( int playerId );
	Player*		GetPlayer( int playerId ) { return m_PlayerList[playerId]; }

	// set Player data
	void SetPosition( unsigned int playerId, DDVECTOR3 pos ) { m_PlayerList[playerId]->SetPosition( pos ); }
	void SetScale( unsigned int playerId, DDVECTOR3 scale ){ m_PlayerList[playerId]->SetScale( scale ); }
	void SetRotation( unsigned int playerId, DDVECTOR3 rotation ){ m_PlayerList[playerId]->SetRotation( rotation ); }
	void SetVelocity( unsigned int playerId, DDVECTOR3 velocity ){ m_PlayerList[playerId]->SetVelocity( velocity ); }

	void GoForward( unsigned int playerId ) { m_PlayerList[playerId]->GoForward(); }
	void Stop( unsigned int playerId ){ m_PlayerList[playerId]->Stop(); }
	void LookAt( unsigned int playerId, float x, float y, float z ) { m_PlayerList[playerId]->LookAt( x, y, z ); }

	// get Player data
	DDVECTOR3 GetPosition( unsigned int playerId ) { return m_PlayerList[playerId]->GetPosition(); }
	DDVECTOR3 GetScale( unsigned int playerId ) { return m_PlayerList[playerId]->GetScale(); }
	DDVECTOR3 GetRotation( unsigned int playerId ) { return m_PlayerList[playerId]->GetRotation(); }
	DDVECTOR3 GetVelocity( unsigned int playerId ) { return m_PlayerList[playerId]->GetVelocity(); }
		
	unsigned int GetCurrentPlayers() const { return m_CurrentPlayers; }

private:

	// player list
	unsigned int	m_CurrentPlayers = 0;
	std::array<Player*, MAX_PLAYER_NUM> 	m_PlayerList;
};

extern std::shared_ptr<PlayerManager> g_PlayerManager;