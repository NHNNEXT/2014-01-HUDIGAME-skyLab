#include "stdafx.h"
#include "PlayerManager.h"
#include "NetworkManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include "MatrixTransform.h"
#include "CompassUI.h"

std::shared_ptr<PlayerManager> GPlayerManager = nullptr;

PlayerManager::PlayerManager()
{
	// 생성과 동시에 세련된 초기화를 할 수 있는 방법이 있을거같은데..ㅠㅠ
	m_PlayerList.fill( nullptr );
}


PlayerManager::~PlayerManager()
{
}


bool PlayerManager::AddPlayer( int playerId )
{
	if ( playerId < 0 || playerId >= MAX_PLAYER_NUM )
		return false;

	// 캐릭터 있으면 리턴
	if ( m_PlayerList[playerId] != nullptr )
		return false;

	// 없으면 새 캐릭터 만듦
	m_PlayerList[playerId] = Player::Create( playerId );
	m_PlayerList[playerId]->Init();	

	GSceneManager->GetScene()->AddChild( m_PlayerList[playerId] );
	++m_CurrentPlayers;	

	return true;
}


void PlayerManager::DeletePlayer( int playerId )
{
	if ( m_PlayerList[playerId] != nullptr )
	{
		delete m_PlayerList[playerId];
		m_PlayerList[playerId] = nullptr;

		--m_CurrentPlayers;
	}
}

Player*	PlayerManager::GetMyPlayer()
{ 
	if ( m_MyPlayerId == NOTHING )
		return nullptr;

	return m_PlayerList[m_MyPlayerId];
}

