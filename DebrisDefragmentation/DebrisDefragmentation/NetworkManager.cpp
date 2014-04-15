#include "NetworkManager.h"
#include "DDNetwork.h"
#include "PacketType.h"
#include "GameLogic.h"

NetworkManager* GNetworkManager = nullptr;
int NetworkManager::m_MyPlayerId = -1;

NetworkManager::NetworkManager()
{
}


NetworkManager::~NetworkManager()
{
}

void NetworkManager::SendAcceleration()
{
	AccelerarionRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;

	outPacket.mRotationX = GGameLogic->GetPlayer( m_MyPlayerId )->GetRotationX(); 
	outPacket.mRotationY = GGameLogic->GetPlayer( m_MyPlayerId )->GetRotationY();
	outPacket.mRotationZ = GGameLogic->GetPlayer( m_MyPlayerId )->GetRotationZ();

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::SendStop()
{
	StopRequest  outPacket;

	outPacket.mPlayerId = m_MyPlayerId;

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::SendRotation( double y, double x )
{
	RotationRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;

	outPacket.mRotationX = GGameLogic->GetPlayer( m_MyPlayerId )->GetRotationX();
	outPacket.mRotationY = GGameLogic->GetPlayer( m_MyPlayerId )->GetRotationY();
	outPacket.mRotationZ = GGameLogic->GetPlayer( m_MyPlayerId )->GetRotationZ();

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::RegisterHandles()
{
	// 여기에서 핸들러를 등록하자
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_LOGIN, HandleLoginResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_ACCELERATION, HandleAccelerationResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_STOP, HandleStopResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_ROTATION, HandleRotationResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_SYNC, HandleLoginResult );
}

void NetworkManager::HandleLoginResult( DDPacketHeader& pktBase )
{
	// 일단 저기서 얼마만큼 읽어와서 해당 패킷을 구성하고
	LoginResult inPacket = reinterpret_cast<LoginResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );
	
	// 로그인 해있는 상태에서 다른 플레이어가 추가로 로그인 할 경우
	if ( NULL != m_MyPlayerId )
	{
		GGameLogic->AddPlayer();	
		//GGameLogic->GetScene()->AddChild(GGameLogic->getp)
		return;
	}
	
	// 사용자의 player가 최초 로그인한 경우
	m_MyPlayerId = inPacket.mPlayerId;
	for ( unsigned int i = 0; i < m_MyPlayerId; ++i )
	{		
		GGameLogic->AddPlayer();
	}
}

void NetworkManager::HandleAccelerationResult( DDPacketHeader& pktBase )
{
	AccelerarionResult inPacket = reinterpret_cast<AccelerarionResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

}

void NetworkManager::HandleStopResult( DDPacketHeader& pktBase )
{
	StopResult inPacket = reinterpret_cast<StopResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

}

void NetworkManager::HandleRotationResult( DDPacketHeader& pktBase )
{
	RotationResult inPacket = reinterpret_cast<RotationResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

}

void NetworkManager::HandleSyncResult( DDPacketHeader& pktBase )
{
	SyncResult inPacket = reinterpret_cast<SyncResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

}
