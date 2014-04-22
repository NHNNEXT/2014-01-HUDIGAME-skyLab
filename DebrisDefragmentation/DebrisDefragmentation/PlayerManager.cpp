#include "PlayerManager.h"
#include "NetworkManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "PlayScene.h"

std::shared_ptr<PlayerManager> g_PlayerManager = nullptr;

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

	// 캐릭터 없으면 리턴
	if ( m_PlayerList[playerId] != nullptr )
		return false;

	// 새 캐릭터 만듦
	m_PlayerList[playerId] = Player::Create( playerId );
	m_PlayerList[playerId]->Init();

	g_SceneManager->GetScene()->AddChild( m_PlayerList[playerId] );
	++m_CurrentPlayers;

	// 처음 연결일 때, 현재 사용자의 플레이어일 것이므로 player ID set
	if ( GNetworkManager->GetMyPlayerId() == -1 )
	{
		GNetworkManager->SetMyPlayerId( playerId );
	}


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