#include "stdafx.h"
#include "GameManager.h"
#include "ClientManager.h"
#include "ClientSession.h"

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
		GClientManager->GetSession( idx )->BroadcastKineticState();
		// 위치, 속도, 스핀
		break;
	case ClassSkill::OCCUPY:
	case ClassSkill::DESTROY:
		// ISS 특정 모듈 정보
		GClientManager->BroadcastModuleState( idx );
		break;
	case ClassSkill::SHARE_FUEL:
	case ClassSkill::SHARE_OXYGEN:
		GClientManager->GetSession( idx )->BroadcastCharacterState();
		break;
	case ClassSkill::MOVE_FAST:
	case ClassSkill::EMP:
		// 대상 캐릭터 - 내부 변수 잠시 수정해서 사용하도록
		// 대상 팀
		break;
	case ClassSkill::WARNING:
		// 이벤트 타입, 남은 시간
		break;
	case ClassSkill::GATHER:
		// 누가, 얼마나 채취
		break;
	case ClassSkill::SET_MINE:
	case ClassSkill::SET_SENTRY_GUN:
	case ClassSkill::SET_DESPENSER:
		// 새로운 오브젝트 추가 - 오브젝트 타입, 위치, 소유자
		break;
	default:
		break;
	}
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
		printf_s( "collision : %d \n", each );
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
	if ( m_WinnerTeam != TeamColor::NO_TEAM )
	{
		// 방송 요청
		GameResultResult outPacket;
		outPacket.mWinnerTeam = static_cast<int>( m_WinnerTeam );

		GClientManager->BroadcastPacket( nullptr, &outPacket );
	}
}