#include "NetworkManager.h"
#include "DDNetwork.h"
#include "PacketType.h"
#include "PlayerManager.h"

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

void NetworkManager::SendRotateDirection( float x, float y )
{
	if ( m_MyPlayerId == -1 )
		return;

	RotationRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;

	outPacket.mRotationX = x;
	outPacket.mRotationY = y;
	outPacket.mRotationZ = .0f;

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::RegisterHandles()
{
	// 여기에서 핸들러를 등록하자
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_LOGIN, HandleLoginResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_ACCELERATION, HandleGoForwardResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_STOP, HandleStopResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_ROTATION, HandleLookAtResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_SYNC, HandleSyncResult );
}

void NetworkManager::HandleLoginResult( DDPacketHeader& pktBase )
{
	// 일단 저기서 얼마만큼 읽어와서 해당 패킷을 구성하고
	LoginResult inPacket = reinterpret_cast<LoginResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

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
	g_PlayerManager->GoForward( inPacket.mPlayerId );
	g_PlayerManager->SetPosition( inPacket.mPlayerId, DDVECTOR3( inPacket.mPosX, inPacket.mPosY, inPacket.mPosZ ) );
	g_PlayerManager->SetRotation( inPacket.mPlayerId, DDVECTOR3( inPacket.mRotationX, inPacket.mRotationY, inPacket.mRotationZ ) );
	g_PlayerManager->SetVelocity( inPacket.mPlayerId, DDVECTOR3( inPacket.mVelocityX, inPacket.mVelocityY, inPacket.mVelocityZ ) );
}

void NetworkManager::HandleStopResult( DDPacketHeader& pktBase )
{
	StopResult inPacket = reinterpret_cast<StopResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );
		
	g_PlayerManager->AddPlayer( inPacket.mPlayerId );	
	g_PlayerManager->Stop( inPacket.mPlayerId );
	g_PlayerManager->SetPosition( inPacket.mPlayerId, DDVECTOR3( inPacket.mPosX, inPacket.mPosY, inPacket.mPosZ ) );
}

void NetworkManager::HandleLookAtResult( DDPacketHeader& pktBase )
{
	RotationResult inPacket = reinterpret_cast<RotationResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	g_PlayerManager->AddPlayer( inPacket.mPlayerId );
	g_PlayerManager->LookAt( inPacket.mPlayerId, inPacket.mRotationX, inPacket.mRotationY, inPacket.mRotationZ );
}

void NetworkManager::HandleSyncResult( DDPacketHeader& pktBase )
{
	SyncResult inPacket = reinterpret_cast<SyncResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	g_PlayerManager->AddPlayer( inPacket.mPlayerId );
	g_PlayerManager->SetPosition( inPacket.mPlayerId, DDVECTOR3( inPacket.mPosX, inPacket.mPosY, inPacket.mPosZ ) );
	g_PlayerManager->SetRotation( inPacket.mPlayerId, DDVECTOR3( inPacket.mRotationX, inPacket.mRotationY, inPacket.mRotationZ ) );
	g_PlayerManager->SetVelocity( inPacket.mPlayerId, DDVECTOR3( inPacket.mVelocityX, inPacket.mVelocityY, inPacket.mVelocityZ ) );
}
