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

	outPacket.mRotationX = 0.0f; // 일단 내 캐릭터 불러 올 수 있게 만들고 수정
	outPacket.mRotationX = 0.0f; // 일단 내 캐릭터 불러 올 수 있게 만들고 수정
	outPacket.mRotationX = 0.0f; // 일단 내 캐릭터 불러 올 수 있게 만들고 수정

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

	outPacket.mRotationX = 0.0f; // 일단 내 캐릭터 불러 올 수 있게 만들고 수정
	outPacket.mRotationX = 0.0f; // 일단 내 캐릭터 불러 올 수 있게 만들고 수정
	outPacket.mRotationX = 0.0f; // 일단 내 캐릭터 불러 올 수 있게 만들고 수정

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}