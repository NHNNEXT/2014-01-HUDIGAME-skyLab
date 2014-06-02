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

void GameManager::BroadcastSkillResult( int idx, ClassSkill skillType )
{
	// 매니저에게 접근해서
	// 어떻게든 세션을 알아내서 스킬 타입에 따라서 적합한 패킷을 방송하도록 시킨다
	// 각각의 스킬들의 성격이 다른데  
	switch ( skillType )
	{
	case ClassSkill::PUSH:
	case ClassSkill::PULL:
		// 위치, 속도, 스핀
		assert( GClientManager->GetSession( idx ) );
		GClientManager->GetSession( idx )->BroadcastKineticState( true, true );
		break;
	case ClassSkill::OCCUPY:
	case ClassSkill::DESTROY:
		// ISS 특정 모듈 정보
		GClientManager->BroadcastModuleState( idx );
		break;
	case ClassSkill::SHARE_FUEL:
	case ClassSkill::SHARE_OXYGEN:
	case ClassSkill::MOVE_FAST:
	case ClassSkill::EMP:
		assert( GClientManager->GetSession( idx ) );
		GClientManager->GetSession( idx )->BroadcastCharacterState();
		break;
	case ClassSkill::WARNING:
		assert( GClientManager->GetSession( idx ) );
		GClientManager->GetSession( idx )->SendWarning();
		break;
	case ClassSkill::GATHER:
		// 누가, 얼마나 채취
		assert( GClientManager->GetSession( idx ) );
		GClientManager->GetSession( idx )->BroadcastGatherResult();
		break;
	default:
		break;
	}
}

void GameManager::BroadcastCharacterChange( int idx, ChangeType type )
{
	switch ( type )
	{
	case ChangeType::KINETIC_STATE:
		GClientManager->GetSession( idx )->BroadcastKineticState( true, true );
		break;
	case ChangeType::CHARACTER_STATE:
		GClientManager->GetSession( idx )->BroadcastCharacterState();
		break;
	case ChangeType::GAME_EVENT_SATE:
		break;
	default:
		break;
	}
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
