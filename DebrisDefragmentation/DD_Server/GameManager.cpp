#include "stdafx.h"
#include "GameManager.h"
#include "ClientManager.h"
#include "ClientSession.h"

#include "LogManager.h"

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::BroadcastCharacterChange( int targetId, ChangeType type )
{
	ClientSession* targetSession = GClientManager->GetSession( targetId );
	assert( targetSession );

	switch ( type )
	{
	case ChangeType::KINETIC_STATE:
		targetSession->BroadcastKineticState( true, true );
		break;
	case ChangeType::CHARACTER_STATE:
		targetSession->BroadcastCharacterState( );
		break;
	case ChangeType::DISASTER_EVENT_STATE:
		// 조심해!
		// 이건 따로 분리해야 하나...
		targetSession->SendWarning( );
		break;
	case ChangeType::RESOURCE_GATHER:
		targetSession->BroadcastGatherResult( );
		break;
	default:
		break;
	}
}

void GameManager::BroadcastIssChange()
{
	GClientManager->BroadcastModuleState();
}

void GameManager::BroadcastStructureInstallation( int structureId, StructureType structureType, D3DXVECTOR3 position, D3DXVECTOR3 direction, TeamColor teamColor )
{
	StructureInstallResult outPacket;

	outPacket.mStructInfo.mStructureId = structureId;
	outPacket.mStructInfo.mStructureType = static_cast<int>( structureType );
	outPacket.mStructInfo.mPosition = position;
	outPacket.mStructInfo.mDirection = direction;
	outPacket.mStructInfo.mTeamColor = static_cast<int>( teamColor );

	GClientManager->BroadcastPacket( nullptr, &outPacket );
}

void GameManager::BroadcastStructureUninstallation( int structureId, StructureType structureType )
{
	StructureUninstallResult outPacket;

	outPacket.mStructureId = structureId;
	outPacket.mStructureType = static_cast<int>( structureType );

	GClientManager->BroadcastPacket( nullptr, &outPacket );
}

void GameManager::DoPeriodWork() 
{
	// 게임 로직이 주기적으로 실행되는 곳이므로 게임 내 상태 변화는 여기서 일어나고
	// 상태가 바뀐 부분(충돌이나 죽음, 게임 종료)에 한정해서 방송합니다
	// 주기적 polling이 많은 패킷을 유발하는 것은 방송할 필요가 없는 상태까지 똑같이 방송할 때 생기는 것 아닌가요??

	// 충돌 이벤트를 여기서 방송하는 이유는 충돌 판정이 되었을 때 바로 방송할 경우 
	// 특정 캐릭터가 여러 오브젝트와 동시에 충돌할 경우, 각각의 충돌 판정 수만큼 패킷을 보내므로 중복이라고 생각해서
	// 충돌 판정 된 캐릭터들 리스트를 생성하고 일괄적으로 한번씩만 보내기 위함이거든요.

	// 게임 로직 진행
	Update();

	// 충돌 결과 방송
	std::for_each( m_CollidedPlayers.begin(), m_CollidedPlayers.end(), []( const int& each )
	{
		// 방송 요청
		ClientSession* targetSession = GClientManager->GetSession( each );
		if ( targetSession )
			targetSession->BroadcastCollisionResult();
		else
			DDLOG_WARN( L"invalid index" );
		// printf_s( "collision : %d \n", each );
	}
	);
	m_CollidedPlayers.clear();

	// 죽음(산소 == 0) 방송
	std::for_each( m_DeadPlayers.begin(), m_DeadPlayers.end(), []( const int& each )
	{
		// 방송 요청
		ClientSession* targetSession = GClientManager->GetSession( each );
		if ( targetSession )
			targetSession->BroadcastDeadResult();
		else
			DDLOG_WARN( L"invalid index" );
	}
	);
	m_DeadPlayers.clear();

	// 게임 종료 조건 확인
	if ( m_WinnerTeam != TeamColor::NO_TEAM && !m_GameEndFlag )
	{
		DDLOG_INFO( L"game end" );
		m_GameEndFlag = true;

		// 방송 요청
		GameResultResult outPacket;
		outPacket.mWinnerTeam = static_cast<int>( m_WinnerTeam );

		GClientManager->BroadcastPacket( nullptr, &outPacket );
	}
}

void GameManager::BroadcastDispenserEffect( int idx, bool dispenserEffectFlag )
{
	ClientSession* targetSession = GClientManager->GetSession( idx );
	if ( targetSession )
		targetSession->BroadcastDispenserEffect( dispenserEffectFlag );
	else
		DDLOG_WARN( L"invalid index" );
}

void GameManager::BroadcastDisasterOccurrence( D3DXVECTOR3 direction, float remainTime )
{
	DisaterOccurrenceResult outPacket;

	outPacket.direction = direction;
	outPacket.remainTime = remainTime;

	GClientManager->BroadcastPacket( nullptr, &outPacket );
}

void GameManager::BroadcastDestroyISSResult( D3DXVECTOR3 direction, D3DXVECTOR3 position )
{
	DestroyISSResult outPacket;

	outPacket.mDirection = direction;
	outPacket.mHitPosition = position;

	GClientManager->BroadcastPacket( nullptr, &outPacket );
}
