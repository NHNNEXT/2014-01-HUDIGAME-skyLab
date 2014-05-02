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
	if ( USE_LOCAL_SERVER )
	{
		DDNetwork::GetInstance()->Connect( "localhost", 9001 );
	}
	else
	{
		DDNetwork::GetInstance()->Connect( "10.73.45.144", 9001 );
	}
	
	
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

	D3DXVECTOR3 angles = g_PlayerManager->GetCameraViewingDirection();

	outPacket.mRotationX = angles.x;
	outPacket.mRotationY = angles.y;
	outPacket.mRotationZ = angles.z;
// 	outPacket.mRotationX = D3DXToDegree( angles.x );
// 	outPacket.mRotationY = D3DXToDegree( angles.y );
// 	outPacket.mRotationZ = D3DXToDegree( angles.z );

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

	// camera 방향으로 push 발사
	outPacket.mRotationX = g_PlayerManager->GetCameraViewingDirection().x;
	outPacket.mRotationY = g_PlayerManager->GetCameraViewingDirection().y;
	outPacket.mRotationZ = g_PlayerManager->GetCameraViewingDirection().z;
// 	outPacket.mRotationX = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationX();
// 	outPacket.mRotationY = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationY();
// 	outPacket.mRotationZ = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationZ();

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
	
	// camera 방향으로 pull 발사
	outPacket.mRotationX = g_PlayerManager->GetCameraViewingDirection().x;
	outPacket.mRotationY = g_PlayerManager->GetCameraViewingDirection().y;
	outPacket.mRotationZ = g_PlayerManager->GetCameraViewingDirection().z;

// 	outPacket.mRotationX = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationX();
// 	outPacket.mRotationY = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationY();
// 	outPacket.mRotationZ = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetRotationZ();

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
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->TurnBody(inPacket.mRotationX, inPacket.mRotationY, inPacket.mRotationZ );
	if ( inPacket.mPlayerId == m_MyPlayerId )
	{
		g_PlayerManager->GetCamera()->SetRotation( ZERO_VECTOR3 );
	}
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->StopSpin();
}

void NetworkManager::HandleSyncResult( DDPacketHeader& pktBase )
{
	SyncResult inPacket = reinterpret_cast<SyncResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	g_PlayerManager->AddPlayer( inPacket.mPlayerId );
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->SetPosition(DDVECTOR3( inPacket.mPosX, inPacket.mPosY, inPacket.mPosZ ) );
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

	if ( inPacket.mSpinAxisX == 0.0f && inPacket.mSpinAxisY == 0.0f && inPacket.mSpinAxisZ == 0.0f )
		return;

	player->SetSpin( DDVECTOR3( inPacket.mSpinAxisX, inPacket.mSpinAxisY, inPacket.mSpinAxisZ ), inPacket.mSpinAngularVelocity );
	// player->SetSpin( DDVECTOR3( 1.0f, 1.0f, 0.0f ), inPacket.mSpinAngularVelocity );

	printf_s( "[SKILL] PUSH from %d player\n", inPacket.mPlayerId );
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

	if ( inPacket.mSpinAxisX == 0.0f && inPacket.mSpinAxisY == 0.0f && inPacket.mSpinAxisZ == 0.0f )
		return;

	player->SetSpin( DDVECTOR3( inPacket.mSpinAxisX, inPacket.mSpinAxisY, inPacket.mSpinAxisZ ), inPacket.mSpinAngularVelocity );

	printf_s( "[SKILL] PULL from %d player\n", inPacket.mPlayerId );
}