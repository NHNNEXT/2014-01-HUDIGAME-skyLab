#pragma once

#include <unordered_map>
#include <WinSock2.h>
#include "GameManager.h"

class ClientSession;
struct PacketHeader;

class ClientManager
{
public:
	ClientManager() : mLastGCTick( 0 ), mLastClientWorkTick( 0 ), mLastSyncDebugTick( 0 )
	{}
	~ClientManager() {}

	void Init();

	ClientSession* CreateClient( SOCKET sock );

	void BroadcastPacket( ClientSession* from, PacketHeader* pkt );
	void BroadcastModuleState();

	void OnPeriodWork();
	void FlushClientSend();

	// 반드시 고스트 정보 동기화 용도로만 사용할 것
	void SyncGhostInfo();
	void SyncServerDebugInfo();

	// 다른 플레이어들 정보를 가져옴 - 처음 접속한 세션에서 호출
	void InitPlayerState( ClientSession* caller );

	// 새롭게 추가된 mClientIdList에 세션을 등록하고, 삭제하는 함수
	// session에서 호출한다.
	void RegisterSession( int idx, ClientSession* session );
	void DeregisterSession( int idx, ClientSession* session );
	ClientSession* GetSession( int idx ) { return mClientIdList[idx]; }

private:
	void CollectGarbageSessions();
	void ClientPeriodWork();

private:
	typedef std::unordered_map<SOCKET, ClientSession*> ClientList;
	ClientList					mClientList;
	GameManager					mGameManager;

	// 직접 패킷을 보낼 때 id를 기반으로 보내기 위한 자료구조
	// ClientList의 키를 id로 사용하는 것을 고려했으나
	// 현재 id로 사용하는 값은 게임 로직내에서 id의 의미가 강하므로 지금처럼 ActorManager가 id를 발급하는 것이 맞다고 판단 - 접속이 이루어진 후에 
	// 그래서 id를 기반으로 session에 바로 접근할 수 있는 자료구조 가운데, 현재 최대 인원이 8명으로 정해져있으므로 std::array 사용
	std::array<ClientSession*, REAL_PLAYER_NUM>	mClientIdList;

	DWORD			mLastGCTick;
	DWORD			mLastClientWorkTick;
	DWORD			mLastSyncDebugTick;
};

extern ClientManager* GClientManager;