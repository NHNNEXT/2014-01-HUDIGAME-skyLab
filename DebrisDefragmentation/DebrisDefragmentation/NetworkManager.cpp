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