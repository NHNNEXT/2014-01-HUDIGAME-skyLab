#pragma once

#include "GameOption.h"
#include "ISS.h"
#include "Event.h"
#include "Debris.h"

class Character;
class Dispenser;
class SpaceMine;

class ActorManager
{
public:
	ActorManager();
	~ActorManager();

	void Init( );

	virtual void BroadcastSkillResult(int idx, ClassSkill skillType ) = 0;
	virtual void BroadcastCharacterChange( int idx, ChangeType type ) = 0;
	virtual void BroadcastDispenserEffect( int idx, bool dispenserEffectFlag ) = 0;
	
	// 	클라이언트 처음 접속하면 클라이언트 세션이 해당 플레이어의 액터-게임 캐릭터-를 등록한다.
	// 	클라이언트 세션의 멤버 액터의 포인터를 인자로 넣어서 등록하고,
	// 	매니저는 등록된 인덱스값을 actorId로 사용하도록 반환한다.
	int		RegisterCharacter( Character* newCharacter );

	/*
		클라이언트 세션이 선택하고 있는 캐릭터를 다른 것으로 변경(나중에 추가될 클래스 시스템에서 클래스 교체)
		새롭게 등록할 캐릭터 포인터와 id를 넘겨서 등록한다.
	*/
	// void	ChangeActor( Actor* newActor, int actorId );
	void	DeregisterCharacter( int characterId );
	
	// update - 일단 가지고 있는 플레이어들 상태를 업데이트 한다.
	void Update();

	// 인자로 받은 id가 유효한지( list에 등록되어 있는지 ) 판정
	bool IsValidId( int characterId );
	
	// 입력된 아이디의 캐릭터가 바라보는 방향에 있는 캐릭터 중 가장 가까이 있는 캐릭터의 아이디를 반환	
	std::tuple<int, D3DXVECTOR3> DetectTarget( int characterId, const D3DXVECTOR3& direction );

	ISS* GetIss() { return &m_ISS; }

	// 점령 스킬을 사용한 결과 - 모듈이름, 바뀐 소유주, ISS위치, ISS 속도 - 를 반환	
	bool OccupyISS( int characterId, D3DXVECTOR3 direction );
	
	// 파괴 스킬을 사용한 결과 - 모듈이름, 체력 - 를 반환	
	bool DestroyISS( int characterId, D3DXVECTOR3 direction );

	bool BuildDispenser( int characterId, D3DXVECTOR3 direction );
	Dispenser* GetLastSturture() { return m_DispenserList.back(); }	

	int	InstallMine( const D3DXVECTOR3& position, const D3DXVECTOR3& direction, TeamColor team );
	void UninstallMine( unsigned int targetId );

	// 현재 ISS 위치 및 속도 정보 리턴
	float GetIssPositionZ() { return m_ISS.GetPosition(); }
	float GetIssVelocityZ() { return m_ISS.GetVelocity(); }

	// 현재 ISS 각 모듈의 소유자 및 체력 정보 반환
	std::tuple<TeamColor, float> GetModuleState( int moduleIdx );

	const CollisionBox* GetModuleBoundingBox( int moduleIdx );

	const std::array<Debris*, RESOURCE_DEBRIS_NUMBER>& GetResourceDebrisList() const { return m_ResourceDebrisList; }
	void RemoveResourceDebris( int index );

	const std::array<Character*, MAX_PLAYER_NUM>& GetCharacterList() const { return m_CharacterList; }

	// 입력받은 범위 안에 있는 캐릭터 id반환		
	std::vector<int> DetectTargetsInRange( int characterId, float range );

	// get other object data
	// 지금은 없습니다.
	
	// random Seed 반환
	int	 GetRandomSeed() { return m_RandomSeed; }

	int GetGatheredDebris() const { return m_GatheredDebris; }
	void SetGatheredDebris( int val ) { m_GatheredDebris = val; }

	Event* GetEvent() { return &m_Event; }

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

	Event		m_Event;
	ISS			m_ISS;
	TeamColor	m_WinnerTeam = TeamColor::NO_TEAM;

	std::list<Dispenser*>		m_DispenserList;

	std::map<unsigned, SpaceMine*>	m_SpaceMineList;
	unsigned int					m_SpaceMineId = 0;

	
	// 자원 데브리의 정보를 관리
	std::array<Debris*, RESOURCE_DEBRIS_NUMBER>		m_ResourceDebrisList;	

	// 새로운 플레이어가 들어왔을 때, 이미 채취된 데브리 정보를 넘겨주기 위한 리스트
	std::array<int, RESOURCE_DEBRIS_NUMBER>			m_GatheredDebrisList;	

	// 패킷 전송을 위해 게임 내에서 마지막에 채취된 데브리의 id를 기록하는 변수
	int		m_GatheredDebris = -1;
	
	// 서버-클라이언트 랜덤 숫자 생성시 사용할 공통 시드를 저장
	int		m_RandomSeed = 0;

	// other objects
	// 지금은 없음요
};