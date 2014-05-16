#pragma once

#include "GameOption.h"
#include "ISS.h"

class Character;

class ActorManager
{
public:
	ActorManager();
	~ActorManager();

	void Init( );

	virtual void BroadcastSkillResult(int idx, ClassSkill skillType ) = 0;

	/* 
		클라이언트 처음 접속하면 클라이언트 세션이 해당 플레이어의 액터-게임 캐릭터-를 등록한다.
		클라이언트 세션의 멤버 액터의 포인터를 인자로 넣어서 등록하고,
		매니저는 등록된 인덱스값을 actorId로 사용하도록 반환한다.
	*/ 
	int		RegisterCharacter( Character* newCharacter );

	/*
		클라이언트 세션이 선택하고 있는 캐릭터를 다른 것으로 변경(나중에 추가될 클래스 시스템에서 클래스 교체)
		새롭게 등록할 캐릭터 포인터와 id를 넘겨서 등록한다.
	*/
	// void	ChangeActor( Actor* newActor, int actorId );
	void	DeleteCharacter( int characterId );

	
	// update - 일단 가지고 있는 플레이어들 상태를 업데이트 한다.
	void Update();
	/*
		인자로 받은 id가 유효한지(list에 등록되어 있는지) 판정
	*/
	bool IsValidId( int characterId );
	// Actor* GetActor( int actorId ) { return m_ActorList[actorId]; }

	/*
		입력된 아이디의 캐릭터가 바라보는 방향에 있는 캐릭터 중 가장 가까이 있는 캐릭터의 아이디를 반환
	*/
	std::tuple<int, D3DXVECTOR3> DetectTarget( int characterId, const D3DXVECTOR3& direction );

	/*
		점령 스킬을 사용한 결과 - 모듈이름, 바뀐 소유주, ISS위치, ISS 속도 - 를 반환
	*/
	bool OccupyISS( int characterId, D3DXVECTOR3 direction );

	/*
		파괴 스킬을 사용한 결과 - 모듈이름, 체력 - 를 반환
	*/
	bool DestroyISS( int characterId, D3DXVECTOR3 direction );

	/*
		현재 ISS 위치 및 속도 정보 리턴
	*/
	float GetIssPositionZ() { return m_ISS.GetTransform()->GetPositionZ(); }
	float GetIssVelocityZ() { return m_ISS.GetVelocity().z; }

	/*
		현재 ISS 각 모듈의 소유자 및 체력 정보 반환
	*/
	std::tuple<TeamColor, float> GetModuleState( int moduleIdx );

	// get other object data
	// 지금은 없습니다.

protected:
	// 지금은 싱글 스레드니까 락은 필요없다.
	// SRWLOCK m_SRWLock;

	void CheckCollision();

	DWORD m_PrevTime = 0;

	// 충돌한 아이들 저장하기 위한 변수
	std::set<int>						m_CollidedPlayers;
	std::set<int>						m_DeadPlayers;

	// player list
	std::array<Character*, MAX_PLAYER_NUM>	m_CharacterList;

	// teamList - playerId를 저장
	std::set<int> m_TeamBlue;
	std::set<int> m_TeamRed;

	ISS			m_ISS;
	TeamColor	m_WinnerTeam = TeamColor::NO_TEAM;

	// other objects
	// 지금은 없음요
};