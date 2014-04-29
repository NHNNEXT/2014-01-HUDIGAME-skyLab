#include "stdafx.h"
#include "DD_Server.h"
#include "..\..\PacketType.h"
#include "ClientSession.h"
#include "ClientManager.h"

ClientManager* GClientManager = nullptr;

ClientSession* ClientManager::CreateClient( SOCKET sock )
{
	assert( LThreadType == THREAD_CLIENT );

	ClientSession* client = new ClientSession( sock );
	mClientList.insert( ClientList::value_type( sock, client ) );
	client->SetActorManager( &m_ActorManager );

	return client;
}

void ClientManager::BroadcastPacket( ClientSession* from, PacketHeader* pkt )
{
	///FYI: C++ STL iterator 스타일의 루프
	for ( ClientList::const_iterator it = mClientList.begin(); it != mClientList.end(); ++it )
	{
		ClientSession* client = it->second;

		if ( from == client )
			continue;

		client->SendRequest( pkt );
	}
}

void ClientManager::OnPeriodWork()
{
	/// 접속이 끊긴 세션들 주기적으로 정리 (1초 정도 마다 해주자)
	DWORD currTick = GetTickCount();
	if ( currTick - mLastGCTick >= 1000 )
	{
		CollectGarbageSessions();
		mLastGCTick = currTick;
	}

	/// 접속된 클라이언트 세션별로 주기적으로 해줘야 하는 일 (주기는 알아서 정하면 됨 - 지금은 1초로 ㅎㅎ)
	if ( currTick - mLastClientWorkTick >= 1000 )
	{
		ClientPeriodWork();
		mLastClientWorkTick = currTick;
	}

	// 게임 상태를 업데이트 하자
	if ( m_ActorManager.Update() )
	{
		// SyncAll();
	}
	SyncAll();

	/// 처리 완료된 DB 작업들 각각의 Client로 dispatch
	// DispatchDatabaseJobResults();

	/// 최종적으로 클라이언트들에 쌓인 send 요청 처리
	FlushClientSend();
}

void ClientManager::CollectGarbageSessions()
{
	std::vector<ClientSession*> disconnectedSessions;

	///FYI: C++ 11 람다를 이용한 스타일
	std::for_each( mClientList.begin(), mClientList.end(),
		[&]( ClientList::const_reference it )
	{
		ClientSession* client = it.second;

		if ( false == client->IsConnected() && false == client->DoingOverlappedOperation() )
			disconnectedSessions.push_back( client );
	}
	);


	///FYI: C언어 스타일의 루프
	for ( size_t i = 0; i<disconnectedSessions.size(); ++i )
	{
		ClientSession* client = disconnectedSessions[i];
		mClientList.erase( client->mSocket );
		delete client;
	}

}

void ClientManager::ClientPeriodWork()
{
	/// FYI: C++ 11 스타일의 루프
	for ( auto& it : mClientList )
	{
		ClientSession* client = it.second;
		client->OnTick();
	}
}

void ClientManager::FlushClientSend()
{
	for ( auto& it : mClientList )
	{
		ClientSession* client = it.second;
		if ( false == client->SendFlush() )
		{
			client->Disconnect();
		}
	}
}

void ClientManager::SyncAll( )
{
	///# ㄷㄷㄷ 너무하다..

	// 조심해!
	// 작업 오버헤드가 너무 큰 것 같은데...
	// 일단 이번 주는 컴퓨터를 믿고 그냥 ㄱㄱ
	int currentSessionId = -1;

	for ( ClientList::const_iterator it = mClientList.begin(); it != mClientList.end(); ++it )
	{
		ClientSession* client = it->second;

		// 		if ( from == client )
		// 			continue;

		client->SyncCurrentStatus();
	}
}