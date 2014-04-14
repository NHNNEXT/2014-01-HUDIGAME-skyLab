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

	return client;
}

void ClientManager::BroadcastPacket( ClientSession* from, PacketHeader* pkt )
{
	///FYI: C++ STL iterator ��Ÿ���� ����
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
	/// ������ ���� ���ǵ� �ֱ������� ���� (1�� ���� ���� ������)
	DWORD currTick = GetTickCount();
	if ( currTick - mLastGCTick >= 1000 )
	{
		CollectGarbageSessions();
		mLastGCTick = currTick;
	}

	/// ���ӵ� Ŭ���̾�Ʈ ���Ǻ��� �ֱ������� ����� �ϴ� �� (�ֱ�� �˾Ƽ� ���ϸ� �� - ������ 1�ʷ� ����)
	if ( currTick - mLastClientWorkTick >= 1000 )
	{
		ClientPeriodWork();
		mLastClientWorkTick = currTick;
	}

	// ���� ���¸� ������Ʈ ����
	GGameLogic->Update();

	/// ó�� �Ϸ�� DB �۾��� ������ Client�� dispatch
	// DispatchDatabaseJobResults();

	/// ���������� Ŭ���̾�Ʈ�鿡 ���� send ��û ó��
	FlushClientSend();
}

void ClientManager::CollectGarbageSessions()
{
	std::vector<ClientSession*> disconnectedSessions;

	///FYI: C++ 11 ���ٸ� �̿��� ��Ÿ��
	std::for_each( mClientList.begin(), mClientList.end(),
		[&]( ClientList::const_reference it )
	{
		ClientSession* client = it.second;

		if ( false == client->IsConnected() && false == client->DoingOverlappedOperation() )
			disconnectedSessions.push_back( client );
	}
	);


	///FYI: C��� ��Ÿ���� ����
	for ( size_t i = 0; i<disconnectedSessions.size(); ++i )
	{
		ClientSession* client = disconnectedSessions[i];
		mClientList.erase( client->mSocket );
		delete client;
	}

}

void ClientManager::ClientPeriodWork()
{
	/// FYI: C++ 11 ��Ÿ���� ����
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
	// ������!
	// �۾� ������尡 �ʹ� ū �� ������...
	// �ϴ� �̹� �ִ� ��ǻ�͸� �ϰ� �׳� ����
	int currentSessionId = -1;

	for ( ClientList::const_iterator it = mClientList.begin( ); it != mClientList.end( ); ++it )
	{
		ClientSession* client = it->second;
		currentSessionId = client->GetPlayerId();

		if ( currentSessionId != -1 )
		{
			DDVECTOR3 position = GGameLogic->GetPosition( currentSessionId );
			DDVECTOR3 rotation = GGameLogic->GetRotation( currentSessionId );
			DDVECTOR3 velocity = GGameLogic->GetRotation( currentSessionId );
			// scale�� �ϴ� ����

			SyncResult outPacket;
			outPacket.mPlayerId = currentSessionId;

			outPacket.mPosX = position.x;
			outPacket.mPosY = position.y;
			outPacket.mPosZ = position.z;

			outPacket.mRotationX = rotation.x;
			outPacket.mRotationY = rotation.y;
			outPacket.mRotationZ = rotation.z;

			outPacket.mVelocityX = velocity.x;
			outPacket.mVelocityY = velocity.y;
			outPacket.mVelocityZ = velocity.z;

			// �߽����� ������� ��ü�� �����ϱ� ���ؼ� from�� nullptr��...
			BroadcastPacket( nullptr, &outPacket );
		}
	}
}