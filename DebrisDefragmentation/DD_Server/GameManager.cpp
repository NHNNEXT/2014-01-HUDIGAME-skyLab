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
	case ChangeType::GAME_EVENT_SATE:
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

	outPacket.mStructureId = structureId;
	outPacket.mStructureType = static_cast<int>( structureType );
	outPacket.mPosition = position;
	outPacket.mDirection = direction;
	outPacket.mTeamColor = static_cast<int>( teamColor );

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
	// 게임 로직 진행
	Update();

	// 충돌 결과 방송
	std::for_each( m_CollidedPlayers.begin(), m_CollidedPlayers.end(), []( const int& each )
	{
		// 방송 요청
		GClientManager->GetSession( each )->BroadcastCollisionResult();
		// printf_s( "collision : %d \n", each );
	}
	);
	m_CollidedPlayers.clear();

	// 죽음(산소 == 0) 방송
	std::for_each( m_DeadPlayers.begin(), m_DeadPlayers.end(), []( const int& each )
	{
		// 방송 요청
		GClientManager->GetSession( each )->BroadcastDeadResult();
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
	GClientManager->GetSession( idx )->BroadcastDispenserEffect( dispenserEffectFlag );
}
