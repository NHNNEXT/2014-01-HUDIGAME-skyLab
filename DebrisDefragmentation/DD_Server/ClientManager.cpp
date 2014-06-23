#include "stdafx.h"
#include "DD_Server.h"
#include "..\..\PacketType.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"
#include <set>
#include <algorithm>
#include "ObjectTable.h"

ClientManager* GClientManager = nullptr;

ClientSession* ClientManager::CreateClient( SOCKET sock )
{
	assert( LThreadType == THREAD_CLIENT );

	ClientSession* client = new ClientSession( sock, &mGameManager );
	mClientList.insert( ClientList::value_type( sock, client ) );

	return client;
}

void ClientManager::RegisterSession( int idx, ClientSession* session ) 
{ 
	assert( mClientIdList[idx] == nullptr );
	mClientIdList[idx] = session;
}

void ClientManager::DeregisterSession( int idx, ClientSession* session ) 
{ 
	assert( mClientIdList[idx] == session );
	mClientIdList[idx] = nullptr; 
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

	if ( mClientList.size() == 0 )
		Init();

	// 게임 로직에 관련 된 것도 진행
	mGameManager.DoPeriodWork();
	
#ifdef USE_CHARACTER_COLLISION_BOX
	// 클라이언트에서 서버 정보 동기화 디버깅용으로 사용했습니다. - 싱크로 오는 정보는 클라 캐릭터가 아닌 고스트에 적용
	SyncGhostInfo();
#endif
	/// 처리 완료된 DB 작업들 각각의 Client로 dispatch
	// DispatchDatabaseJobResults();

	// 서버 디버깅 정보 전송
	if ( currTick - mLastSyncDebugTick >= 1000 )
	{
		SyncServerDebugInfo();
		mLastSyncDebugTick = currTick;
	}

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

void ClientManager::SyncGhostInfo()
{
	// 동기화 디버깅 수단으로 사용
	for ( ClientList::const_iterator it = mClientList.begin(); it != mClientList.end(); ++it )
	{
		ClientSession* client = it->second;

		client->SyncGhostInfo();
	}
}

void ClientManager::SyncServerDebugInfo()
{
	DebugServerInfoResult outPacket;
	
	for ( int i = 0; i < REAL_PLAYER_NUM; ++i )
	{
		Character* tempCharacter = GObjectTable->GetCharacter( i );

		if ( tempCharacter == nullptr )
		{
			outPacket.mPlayerTeam[i] = NOTHING;
			outPacket.mPlayerClass[i] = NOTHING;
		}
		else
		{
			outPacket.mPlayerTeam[i] = static_cast<int>( tempCharacter->GetTeam() );
			outPacket.mPlayerClass[i] = static_cast<int>( tempCharacter->GetClassComponent()->GetCharacterClassName() );
		}
	}

	outPacket.mIssPos = mGameManager.GetIssPositionZ();
	outPacket.mIssPos = mGameManager.GetIssVelocityZ();

	for ( int i = 0; i < MODULE_NUMBER; ++i )
	{
		TeamColor color = TeamColor::NO_TEAM;
		float hp = 1.0f;

		std::tie( color, hp ) = mGameManager.GetModuleState( i );

		outPacket.mModuleOwner[i] = static_cast<int>( color );
		outPacket.mModuleHP[i] = hp;
	}

	BroadcastPacket( nullptr, &outPacket );
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
	mGameManager.Init();
	mClientIdList.fill( nullptr );
}

void ClientManager::BroadcastModuleState()
{
	IssStateResult outPacket;

	outPacket.mIssPositionZ = mGameManager.GetIssPositionZ( );
	outPacket.mIssVelocityZ = mGameManager.GetIssVelocityZ( );

	for ( int i = 0; i < MODULE_NUMBER; ++i )
	{
		TeamColor color = TeamColor::NO_TEAM;
		float hp = 1.0f;

		std::tie( color, hp ) = mGameManager.GetModuleState( i );

		outPacket.mModuleOwner[i] = static_cast<int>( color );
		outPacket.mModuleHP[i] = hp;
	}

	BroadcastPacket( nullptr, &outPacket );
}