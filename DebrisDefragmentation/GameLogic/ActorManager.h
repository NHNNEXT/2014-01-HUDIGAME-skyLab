#pragma once

#include "GameOption.h"
#include <set>
#include "Actor.h"
#include "ISS.h"

class ActorManager
{
public:
	ActorManager();
	~ActorManager();

	void Init( );

	/* 
		클라이언트 처음 접속하면 클라이언트 세션이 해당 플레이어의 액터-게임 캐릭터-를 등록한다.
		클라이언트 세션의 멤버 액터의 포인터를 인자로 넣어서 등록하고,
		매니저는 등록된 인덱스값을 actorId로 사용하도록 반환한다.
		최경욱 2014. 4. 22
	*/ 
	int		RegisterUser( Actor* newActor );

	/*
		클라이언트 세션이 선택하고 있는 캐릭터를 다른 것으로 변경(나중에 추가될 클래스 시스템에서 클래스 교체)
		새롭게 등록할 캐릭터 포인터와 id를 넘겨서 등록한다.
		최경욱 2014. 4. 22
	*/
	// void	ChangeActor( Actor* newActor, int actorId );
	void	DeleteActor( int actorId );

	
	// update - 일단 가지고 있는 플레이어들 상태를 업데이트 한다.
	void Update();

	/*
		인자로 받은 id가 유효한지(list에 등록되어 있는지) 판정
		최경욱 2014. 4. 22
	*/
	bool IsValidId( int actorId );
	Actor* GetActor( int actorId ) { return m_ActorList[actorId]; }

	/*
		입력된 아이디의 캐릭터가 바라보는 방향에 있는 캐릭터 중 가장 가까이 있는 캐릭터의 아이디를 반환
		최경욱 2014. 4. 22
	*/
	std::tuple<int, D3DXVECTOR3> DetectTarget( int actorId, float x, float y, float z );

	/*
		점령 스킬을 사용한 결과 - 모듈이름, 바뀐 소유주, ISS위치, ISS 속도 - 를 반환
		최경욱 2014. 5. 6
	*/
	std::tuple<ISSModuleName, TeamColor, float, float> TryOccupy( int actorId, float x, float y, float z );

	/*
		파괴 스킬을 사용한 결과 - 모듈이름, 체력 - 를 반환
		최경욱 2014. 5. 6
	*/
	std::tuple<ISSModuleName, float> TryDestroy( int actorId, float x, float y, float z );

	/*
		현재 ISS 위치 및 속도 정보 리턴
		최경욱 2014. 5. 6
	*/
	float GetIssPositionZ() { return m_ISS.GetTransform().GetPositionZ(); }
	float GetIssVelocityZ() { return m_ISS.GetVelocity().z; }

	/*
		현재 ISS 각 모듈의 소유자 및 체력 정보 반환
		최경욱 2014. 5. 6
	*/
	std::tuple<TeamColor, float> GetModuleState( int moduleIdx );

	/*
		충돌한 플레이어들의 index를 반환하는 함수
		최경욱 2014. 5. 11
	*/
	std::set<int> GetCollidedPlayerId() { return m_CollidedPlayers; }
	std::set<int> GetDeadPlayerId() { return m_DeadPlayers; }

	/*
		충돌한 플레이어들의 index를 초기화 함수
		클라이언트 매니저가 충돌한 플레이어들 아이디를 받아간 후에는 초기화해서 충돌 결과를 방송한 플레이어를 다시 방송하지 않도록 함
		자체적으로 업데이트 단계에서 충돌 체크 전에 초기화해도 되지만 
		혹시라도 구조 변경때문에 클라이언트 매니저가 내용을 가져 가지 않은 상태에서 다시 진입하는 경우가 생길까봐 위험하지만 외부에서 수동으로 처리
		최경욱 2014. 5. 11
	*/
	void ClearCollidedPlayer() { m_CollidedPlayers.clear(); }
	void ClearDeadPlayer() { m_DeadPlayers.clear(); }

	// get other object data
	// 지금은 없습니다.

private:
	// 지금은 싱글 스레드니까 락은 필요없다.
	// SRWLOCK m_SRWLock;

	void CheckCollision();

	DWORD m_PrevTime = 0;

	// 충돌한 아이들 저장하기 위한 변수
	std::set<int>						m_CollidedPlayers;
	std::set<int>						m_DeadPlayers;

	// player list
	std::array<Actor*, MAX_PLAYER_NUM>	m_ActorList;

	// teamList - playerId를 저장
	std::set<int> m_TeamBlue;
	std::set<int> m_TeamRed;

	ISS									m_ISS;

	// other objects
	// 지금은 없음요
};

