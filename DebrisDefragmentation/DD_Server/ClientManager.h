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

	void Init();

	ClientSession* CreateClient( SOCKET sock );

	void BroadcastPacket( ClientSession* from, PacketHeader* pkt );

	void OnPeriodWork();
	void FlushClientSend();

	// 현재 게임 상태를 접속중인 모든 클라이언트에 동기화 시킴 - 무서운 녀석이다. 봉인
	void SyncAll();

	// 다른 플레이어들 정보를 가져옴 - 처음 접속한 세션에서 호출
	void InitPlayerState( ClientSession* caller );

	// 새롭게 추가된 mClientIdList에 세션을 등록하고, 삭제하는 함수
	// session에서 호출한다.

	///# 한줄에 깔끔하게 안되는 것들은 차라리 CPP로 분리해라. 이 함수가 자주 불리는 것도 아니고.. 인라인 해도 이득이 없다.
	void RegisterSession( int idx, ClientSession* session ) { if ( !mClientIdList[idx] ) mClientIdList[idx] = session; } 
	
	///# 그리고 만일 if 문이 아니면 그냥 넘어가는 함수?? Register / Deregister 쌍은 논리적으로 100% 무결하게 맞아떨어져야 한다. 차라리 assert 활용.
	void DeleteSession( int idx, ClientSession* session ) { if ( mClientIdList[idx] == session ) mClientIdList[idx] = nullptr; } ///# 네이밍 조심: Deregister

private:
	void CollectGarbageSessions();
	void ClientPeriodWork();

private:
	typedef std::unordered_map<SOCKET, ClientSession*> ClientList;
	ClientList						mClientList;

	// 직접 패킷을 보낼 때 id를 기반으로 보내기 위한 자료구조
	// ClientList의 키를 id로 사용하는 것을 고려했으나
	// 현재 id로 사용하는 값은 게임 로직내에서 id의 의미가 강하므로 지금처럼 ActorManager가 id를 발급하는 것이 맞다고 판단 - 접속이 이루어진 후에 
	// 그래서 id를 기반으로 session에 바로 접근할 수 있는 자료구조 가운데, 현재 최대 인원이 8명으로 정해져있으므로 std::array 사용
	std::array<ClientSession*, MAX_PLAYER_NUM>	mClientIdList;

	DWORD			mLastGCTick;
	DWORD			mLastClientWorkTick;
	ActorManager	mActorManager;
};

extern ClientManager* GClientManager;