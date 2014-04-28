#include "NetworkManager.h"
#include "DDNetwork.h"
#include "PacketType.h"
#include "PlayerManager.h"
#include "MatrixTransform.h"

NetworkManager* GNetworkManager = nullptr;
int NetworkManager::m_MyPlayerId = -1;

NetworkManager::NetworkManager()
{
}


NetworkManager::~NetworkManager()
{
}

void NetworkManager::Init()
{
	RegisterHandles();
}

void NetworkManager::Connect()
{
	/// config.h
	//DDNetwork::GetInstance()->Connect( "10.73.42.202", 9001 );
	DDNetwork::GetInstance()->Connect( "localhost", 9001 );
}

void NetworkManager::Disconnect()
{
	DDNetwork::GetInstance()->Disconnect();
}

void NetworkManager::SendAcceleration()
{
	if ( m_MyPlayerId == -1 )
		return;

//	g_PlayerManager->GetPlayer( GNetworkManager->GetMyPlayerId() )->GoForward();

	AccelerarionRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;

	outPacket.mRotationX = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationX(); 
	outPacket.mRotationY = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationY();
	outPacket.mRotationZ = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationZ();

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::SendStop()
{
	if ( m_MyPlayerId == -1 )
		return;

	StopRequest  outPacket;

	outPacket.mPlayerId = m_MyPlayerId;

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

// SendRotation 수정 : lookat 방향으로 몸을 회전하므로 파라미터가 필요없어서.. 이름을 turnbody로 변경
// 04.27 김성환
void NetworkManager::SendTurnBody()
{
	if ( m_MyPlayerId == -1 )
		return;

	printf( "send turn body\n" );
	RotationRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;



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


	// 이 방향이 아닌 카메라의 matrix로 부터 뽑아낸 각도 값으로 packet을 날려야함!!
	D3DXMATRIXA16 rot = g_PlayerManager->GetCamera()->GetMatrix();



	D3DXQUATERNION qt, qtNorm;
	D3DXVECTOR3	tv1, tv2;
	D3DXMatrixDecompose( &tv1, &qt, &tv2, &rot );
	float angleX = 0, angleY = 0, angleZ = 0;

	D3DXQuaternionNormalize( &qtNorm, &qt );

	// quaternion을 axisangle로 바꾸고 다시 yaw pitch roll로 분해, 오차가 큼..
	// 	D3DXVECTOR3 axis( .0f, .0f, .0f );
	// 	float angle = 0;
	// 	D3DXQuaternionToAxisAngle( &qtNorm, &axis , &angle );
	// 	auto angles = GameMatrix::AxisAngleToYawPitchRoll( axis.x, axis.y, axis.z, angle );

	auto angles = GameMatrix::QuaternionToYawPitchRoll( qtNorm );
	std::tie( angleY, angleX, angleZ ) = angles;

	// 	angles = GameMatrix::fromrotmat( rot );
	// 	std::tie( angleY, angleX, angleZ ) = angles;

	outPacket.mRotationX = D3DXToDegree( angleX );
	outPacket.mRotationY = D3DXToDegree( angleY );
	outPacket.mRotationZ = D3DXToDegree( angleZ );

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::SendSkillPush()
{
	if ( m_MyPlayerId == -1 )
		return;

	SkillPushRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;

	outPacket.mPosX = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetPositionX();
	outPacket.mPosY = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetPositionY();
	outPacket.mPosZ = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetPositionZ();

	outPacket.mRotationX = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationX();
	outPacket.mRotationY = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationY();
	outPacket.mRotationZ = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationZ();

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::SendSkillPull()
{
	if ( m_MyPlayerId == -1 )
		return;

	SkillPullRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;

	outPacket.mPosX = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetPositionX();
	outPacket.mPosY = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetPositionY();
	outPacket.mPosZ = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetPositionZ();

	outPacket.mRotationX = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationX();
	outPacket.mRotationY = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationY();
	outPacket.mRotationZ = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationZ();

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::RegisterHandles()
{
	// 여기에서 핸들러를 등록하자
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_LOGIN, HandleLoginResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_ACCELERATION, HandleGoForwardResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_STOP, HandleStopResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_ROTATION, HandleTurnBodyResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_SYNC, HandleSyncResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_SKILL_PUSH, HandlePushResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_SKILL_PULL, HandlePullResult );
}

void NetworkManager::HandleLoginResult( DDPacketHeader& pktBase )
{
	// 일단 저기서 얼마만큼 읽어와서 해당 패킷을 구성하고
	LoginResult inPacket = reinterpret_cast<LoginResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	// 조심해!! AddPlayer 할때 -1 대신 자기 아이디가 리턴되면서 제대로 안들어간다!
	// 사용자의 player가 최초 로그인한 경우
	m_MyPlayerId = inPacket.mPlayerId;

	if ( !g_PlayerManager->AddPlayer( m_MyPlayerId ) )
	{
		// 어떻게 할까요?
	}
}

void NetworkManager::HandleGoForwardResult( DDPacketHeader& pktBase )
{
	AccelerarionResult inPacket = reinterpret_cast<AccelerarionResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );
		
	g_PlayerManager->AddPlayer( inPacket.mPlayerId );
	Player* player = g_PlayerManager->GetPlayer( inPacket.mPlayerId );
	player->GoForward();
	player->SetPosition( DDVECTOR3( inPacket.mPosX, inPacket.mPosY, inPacket.mPosZ ) );
	player->SetRotation( DDVECTOR3( inPacket.mRotationX, inPacket.mRotationY, inPacket.mRotationZ ) );
	player->SetVelocity( DDVECTOR3( inPacket.mVelocityX, inPacket.mVelocityY, inPacket.mVelocityZ ) );
}

void NetworkManager::HandleStopResult( DDPacketHeader& pktBase )
{
	StopResult inPacket = reinterpret_cast<StopResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );
		
	g_PlayerManager->AddPlayer( inPacket.mPlayerId );		
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->Stop();
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->SetPosition( DDVECTOR3( inPacket.mPosX, inPacket.mPosY, inPacket.mPosZ ) );
}

void NetworkManager::HandleTurnBodyResult( DDPacketHeader& pktBase )
{
	RotationResult inPacket = reinterpret_cast<RotationResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	g_PlayerManager->AddPlayer( inPacket.mPlayerId );
	g_PlayerManager->GetPlayer( inPacket.mPlayerId)->TurnBody(inPacket.mRotationX, inPacket.mRotationY, inPacket.mRotationZ );
}

void NetworkManager::HandleSyncResult( DDPacketHeader& pktBase )
{
	SyncResult inPacket = reinterpret_cast<SyncResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	g_PlayerManager->AddPlayer( inPacket.mPlayerId );
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->SetPosition(DDVECTOR3( inPacket.mPosX, inPacket.mPosY, inPacket.mPosZ ) );
	// g_PlayerManager->GetPlayer( inPacket.mPlayerId )->SetRotation(DDVECTOR3( inPacket.mRotationX, inPacket.mRotationY, inPacket.mRotationZ ) );
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->SetVelocity(DDVECTOR3( inPacket.mVelocityX, inPacket.mVelocityY, inPacket.mVelocityZ ) );
}

void NetworkManager::HandlePushResult( DDPacketHeader& pktBase )
{
	SkillPushResult inPacket = reinterpret_cast<SkillPushResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	g_PlayerManager->AddPlayer( inPacket.mTargetId );
	Player* player = g_PlayerManager->GetPlayer( inPacket.mTargetId );
	player->GoForward();
	player->SetPosition( DDVECTOR3( inPacket.mPosX, inPacket.mPosY, inPacket.mPosZ ) );
	player->SetVelocity( DDVECTOR3( inPacket.mVelocityX, inPacket.mVelocityY, inPacket.mVelocityZ ) );

	printf_s( "skill from %d player\n", inPacket.mPlayerId );
}

void NetworkManager::HandlePullResult( DDPacketHeader& pktBase )
{
	SkillPullResult inPacket = reinterpret_cast<SkillPullResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	g_PlayerManager->AddPlayer( inPacket.mTargetId );
	Player* player = g_PlayerManager->GetPlayer( inPacket.mTargetId );
	player->GoForward();
	player->SetPosition( DDVECTOR3( inPacket.mPosX, inPacket.mPosY, inPacket.mPosZ ) );
	player->SetVelocity( DDVECTOR3( inPacket.mVelocityX, inPacket.mVelocityY, inPacket.mVelocityZ ) );

	printf_s( "skill from %d player\n", inPacket.mPlayerId );
}