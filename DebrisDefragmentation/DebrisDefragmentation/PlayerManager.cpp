#include "PlayerManager.h"
#include "NetworkManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "PlayScene.h"

std::shared_ptr<PlayerManager> g_PlayerManager = nullptr;

PlayerManager::PlayerManager()
{
	// ������ ���ÿ� ���õ� �ʱ�ȭ�� �� �� �ִ� ����� �����Ű�����..�Ф�
	m_PlayerList.fill( nullptr );
}


PlayerManager::~PlayerManager()
{
}


bool PlayerManager::AddPlayer( int playerId )
{
	if ( playerId < 0 || playerId >= MAX_PLAYER_NUM )
		return false;

	// ĳ���� ������ ����
	if ( m_PlayerList[playerId] != nullptr )
		return false;

	// �� ĳ���� ����
	m_PlayerList[playerId] = Player::Create( playerId );
	m_PlayerList[playerId]->Init();

	g_SceneManager->GetScene()->AddChild( m_PlayerList[playerId] );
	++m_CurrentPlayers;

	// ó�� ������ ��, ���� ������� �÷��̾��� ���̹Ƿ� player ID set
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