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

	// 특정 캐릭터가 바라보는 방향에 해당하는 타겟의 캐릭터 아이디를 반환
	// 2014. 4. 25 최경욱
	int GetTarget( int characterId ) { return m_ActorManager.DetectTarget( characterId ); }

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