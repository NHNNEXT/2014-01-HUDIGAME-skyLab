#include "PlayerManager.h"
#include "NetworkManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include "MatrixTransform.h"

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

D3DXVECTOR3 PlayerManager::GetCameraViewingDirection()
{
	// quaternion확인용
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

	// quaternion을 axisangle로 바꾸고 다시 yaw pitch roll로 분해, 오차가 큼..
	// 	D3DXVECTOR3 axis( .0f, .0f, .0f );
	// 	float angle = 0;
	// 	D3DXQuaternionToAxisAngle( &qtNorm, &axis , &angle );
	// 	auto angles = GameMatrix::AxisAngleToYawPitchRoll( axis.x, axis.y, axis.z, angle );

	// matrix에서 yaw pitch roll로 바로 분해, 안됨..ㅠㅠ
	// 	angles = GameMatrix::fromrotmat( rot );

	D3DXQUATERNION qt, qtNorm;	// quaternion과 normalized quatenion을 담기 위한 벡터
	D3DXVECTOR3	tv1, tv2, rotationVector3;	/// 리턴벡터 + decompose 시 scale과 position을 담기 위한 임시 벡터
	D3DXMatrixDecompose( &tv1, &qt, &tv2, &rot );
	D3DXQuaternionNormalize( &qtNorm, &qt );

// 	D3DXMATRIXA16 rotMat;
// 	D3DXMatrixIdentity( &rotMat );
// 	D3DXMatrixRotationQuaternion( &rotMat, &qtNorm );
// 	auto ypr = GameMatrix::RotationMatrixToYawPitchRoll( rotMat );

	auto ypr = GameMatrix::QuaternionToYawPitchRoll( qt );

	std::tie( rotationVector3.y, rotationVector3.x, rotationVector3.z ) = ypr;

	return D3DXToDegree(rotationVector3);
}
