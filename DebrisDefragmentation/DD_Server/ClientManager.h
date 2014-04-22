#pragma once

#include <map>
#include <WinSock2.h>
#include "ActorManager.h"

class ClientSession;
struct PacketHeader;

class ClientManager
{
public:
	ClientManager() : mLastGCTick( 0 ), mLastClientWorkTick( 0 )
	{}
	~ClientManager() {}

	ClientSession* CreateClient( SOCKET sock );

	void BroadcastPacket( ClientSession* from, PacketHeader* pkt );

	void OnPeriodWork();
	void FlushClientSend();

	// 현재 게임 상태를 접속중인 모든 클라이언트에 동기화 시킴
	void SyncAll();

private:
	void CollectGarbageSessions();
	void ClientPeriodWork();

private:
	typedef std::map<SOCKET, ClientSession*> ClientList;
	ClientList	mClientList;

	DWORD			mLastGCTick;
	DWORD			mLastClientWorkTick;
	ActorManager	m_ActorManager;
};

extern ClientManager* GClientManager;