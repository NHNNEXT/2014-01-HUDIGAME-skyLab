#include "stdafx.h"
#include "DD_Server.h"
#include "..\..\PacketType.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include <set>
#include <algorithm>

ClientManager* GClientManager = nullptr;

ClientSession* ClientManager::CreateClient( SOCKET sock )
{
	assert( LThreadType == THREAD_CLIENT );

	ClientSession* client = new ClientSession( sock );
	mClientList.insert( ClientList::value_type( sock, client ) );
	client->SetActorManager( &mActorManager );

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

	///# 아래 게임 로직에 해당하는 부분은 사실 따로 분리해서 처리하는게 맞다.
	///# 여기는 클라이언트 세션 관리하는 로직이 있는 곳인데, 게임 콘텐츠가 마구 끼어들면 보기 좋지 않다.
	/// 아래 부분을 전부 ActorManager안에 넣고...   mActorManager->DoPeriodWork(); 이런식으로..


	// 게임 상태를 업데이트 하자
	// 충돌했는지 판단도 여기서함	
	mActorManager.Update();
	std::set<int> collidedIdList = mActorManager.GetCollidedPlayerId();
	mActorManager.ClearCollidedPlayer();

	std::for_each( collidedIdList.begin(), collidedIdList.end(), [&]( const int& each )
	{
		// each 클라이언트별로 BroadcastCollisionResult(); 해줘야 한다
		// 순회할 수는 없는 노릇이고
		// n의 제곱... 리스트를 하나 더 만들어도 되나...
		assert( mClientIdList[each] );
		mClientIdList[each]->BroadcastCollisionResult();
	}
	);

	// 죽은 애들 찾아서 방송하자
	std::set<int> deadPlayer = mActorManager.GetDeadPlayerId();
	mActorManager.ClearDeadPlayer();

	std::for_each( deadPlayer.begin(), deadPlayer.end(), [&]( const int& each )
	{
		// each 클라이언트별로 BroadcastCollisionResult(); 해줘야 한다
		// 순회할 수는 없는 노릇이고
		// n의 제곱... 리스트를 하나 더 만들어도 되나...
		assert( mClientIdList[each] );
		mClientIdList[each]->BroadcastCollisionResult();
	}
	);

	// 조심해!!
	// 뭔가 이벤트 방식이 아니라 풀링 방식이 되어 가는 게 불안하다.
	TeamColor winnerTeam = mActorManager.GetWinnerTeam();
	if ( winnerTeam != TeamColor::NO_TEAM )
	{
		GameResultResult outPacket;
		outPacket.mWinnerTeam = static_cast<int>( winnerTeam );

		BroadcastPacket( nullptr, &outPacket );
	}
	
	SyncAll(); // 클라이언트에서 서버 정보 동기화 디버깅용으로 사용했습니다. - 싱크로 오는 정보는 클라 캐릭터가 아닌 고스트에 적용

	/// 처리 완료된 DB 작업들 각각의 Client로 dispatch
	// DispatchDatabaseJobResults();

	/// 최종적으로 클라이언트들에 쌓인 send 요청 처리
	FlushClientSend();
}

void ClientManager::CollectGarbageSessions()
{
	std::vector<ClientSession*> disconnectedSessions;

	///FYI: C++ 11 람다를 이용한 스타일
	std::for_each( mClientList.begin(), mClientList.end(), [&]( ClientList::const_reference it )
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
	// 동기화 디버깅 수단으로 사용
	for ( ClientList::const_iterator it = mClientList.begin(); it != mClientList.end(); ++it )
	{
		ClientSession* client = it->second;

		client->SyncCurrentStatus();
	}
}

void ClientManager::InitPlayerState( ClientSession* caller )
{

	// 각각의 클라이언트 세션을 돌면서 각자의 상태를 caller에게 전송하는 함수를 호출
	// 그 함수들은 DirectSend를 통해서 
	for ( ClientList::const_iterator it = mClientList.begin(); it != mClientList.end(); ++it )
	{
		ClientSession* client = it->second;

		if ( caller == client )
			continue;

		client->SendCurrentStatus( caller );
	}
}

void ClientManager::Init()
{
	mActorManager.Init();
	std::for_each( mClientIdList.begin(), mClientIdList.end(), []( ClientSession* each )
	{
		each = nullptr;
	} 
	);
}