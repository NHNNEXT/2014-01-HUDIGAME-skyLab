#include "NetworkManager.h"
#include "DDNetwork.h"
#include "PacketType.h"

NetworkManager* GNetworkManger = nullptr;

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

	outPacket.mRotationX = 0.0f; // �ϴ� �� ĳ���� �ҷ� �� �� �ְ� ����� ����
	outPacket.mRotationX = 0.0f; // �ϴ� �� ĳ���� �ҷ� �� �� �ְ� ����� ����
	outPacket.mRotationX = 0.0f; // �ϴ� �� ĳ���� �ҷ� �� �� �ְ� ����� ����

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

	outPacket.mRotationX = 0.0f; // �ϴ� �� ĳ���� �ҷ� �� �� �ְ� ����� ����
	outPacket.mRotationX = 0.0f; // �ϴ� �� ĳ���� �ҷ� �� �� �ְ� ����� ����
	outPacket.mRotationX = 0.0f; // �ϴ� �� ĳ���� �ҷ� �� �� �ְ� ����� ����

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::RegisterHandles()
{
	// ���⿡�� �ڵ鷯�� �������
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_LOGIN, HandleLoginResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_ACCELERATION, HandleAccelerationResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_STOP, HandleStopResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_ROTATION, HandleRotationResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_SYNC, HandleLoginResult );
}

void NetworkManager::HandleLoginResult( DDPacketHeader& pktBase )
{
	// �ϴ� ���⼭ �󸶸�ŭ �о�ͼ� �ش� ��Ŷ�� �����ϰ�
	LoginResult inPacket = reinterpret_cast<LoginResult&>( pktBase );
	
}

void NetworkManager::HandleAccelerationResult( DDPacketHeader& pktBase )
{
	AccelerarionResult inPacket = reinterpret_cast<AccelerarionResult&>( pktBase );

}

void NetworkManager::HandleStopResult( DDPacketHeader& pktBase )
{
	StopResult inPacket = reinterpret_cast<StopResult&>( pktBase );

}

void NetworkManager::HandleRotationResult( DDPacketHeader& pktBase )
{
	RotationResult inPacket = reinterpret_cast<RotationResult&>( pktBase );

}

void NetworkManager::HandleSyncResult( DDPacketHeader& pktBase )
{
	SyncResult inPacket = reinterpret_cast<SyncResult&>( pktBase );

}
