#pragma once

#include <map>
#include <WinSock2.h>
#include "GameLogic.h"

class ClientSession;
struct PacketHeader;

class ClientManager
{
public:
	ClientManager() : mLastGCTick( 0 ), mLastClientWorkTick( 0 )
	{}

	void Init() { m_GameLogic.Init(); }

	ClientSession* CreateClient( SOCKET sock );

	void BroadcastPacket( ClientSession* from, PacketHeader* pkt );

	void OnPeriodWork();
	void FlushClientSend();

private:
	void CollectGarbageSessions();
	void ClientPeriodWork();

private:
	typedef std::map<SOCKET, ClientSession*> ClientList;
	ClientList	mClientList;

	DWORD		mLastGCTick;
	DWORD		mLastClientWorkTick;

	GameLogic	m_GameLogic;
};

extern ClientManager* GClientManager;