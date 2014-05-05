#pragma once

#include <unordered_map>
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

	// 현재 게임 상태를 접속중인 모든 클라이언트에 동기화 시킴 - 무서운 녀석이다. 봉인
	void SyncAll();

	// 다른 플레이어들 정보를 가져옴 - 처음 접속한 세션에서 호출
	void InitPlayerState( ClientSession* caller );

	// 다른 세션에 패킷을 전송
	void DirectSend( const SOCKET& sock, PacketHeader* pkt );

private:
	void CollectGarbageSessions();
	void ClientPeriodWork();

private:
	typedef std::unordered_map<SOCKET, ClientSession*> ClientList;
	ClientList	mClientList;

	DWORD			mLastGCTick;
	DWORD			mLastClientWorkTick;
	ActorManager	m_ActorManager;
};

extern ClientManager* GClientManager;