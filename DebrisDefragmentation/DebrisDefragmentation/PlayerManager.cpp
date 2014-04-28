#include "PlayerManager.h"
#include "NetworkManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include "MatrixTransform.h"

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

std::tuple<float, float, float> PlayerManager::GetCameraViewingDirection()
{
	// quaternionȮ�ο�
	// 	D3DXMATRIXA16 m_Mat = g_PlayerManager->GetPlayer( GNetworkManager->GetMyPlayerId() )->GetMatrix();
	// 	D3DXVECTOR3 m_rot = g_PlayerManager->GetCamera()->GetRotation();
	// 	D3DXVECTOR3 m_scl = g_PlayerManager->GetCamera()->GetScale();
	// 	D3DXVECTOR3 m_pos = g_PlayerManager->GetCamera()->GetPosition();
	// 	D3DXMATRIXA16 m_Mat2;
	// 	D3DXQUATERNION	qRotation;
	// 	D3DXMatrixIdentity( &m_Mat2 );
	// 	D3DXQuaternionRotationYawPitchRoll( &qRotation, D3DXToRadian( m_rot.y ), D3DXToRadian( m_rot.x ), D3DXToRadian( m_rot.z ) );
	// 	D3DXMatrixTransformation( &m_Mat2, NULL, NULL, &m_scl, NULL, &qRotation, &m_pos );
	// 	D3DXMatrixMultiply( &m_Mat2, &m_Mat2, &m_Mat);

	D3DXMATRIXA16 rot = m_Camera->GetMatrix();

	// quaternion�� axisangle�� �ٲٰ� �ٽ� yaw pitch roll�� ����, ������ ŭ..
	// 	D3DXVECTOR3 axis( .0f, .0f, .0f );
	// 	float angle = 0;
	// 	D3DXQuaternionToAxisAngle( &qtNorm, &axis , &angle );
	// 	auto angles = GameMatrix::AxisAngleToYawPitchRoll( axis.x, axis.y, axis.z, angle );

	// matrix���� yaw pitch roll�� �ٷ� ����, �ȵ�..�Ф�
	// 	angles = GameMatrix::fromrotmat( rot );

	D3DXQUATERNION qt, qtNorm;	// quaternion�� normalized quatenion�� ��� ���� ����
	D3DXVECTOR3	tv1, tv2;	/// decompose �� scale�� position�� ��� ���� �ӽ� ����
	D3DXMatrixDecompose( &tv1, &qt, &tv2, &rot );
	D3DXQuaternionNormalize( &qtNorm, &qt );

	return GameMatrix::QuaternionToYawPitchRoll( qtNorm );
}
