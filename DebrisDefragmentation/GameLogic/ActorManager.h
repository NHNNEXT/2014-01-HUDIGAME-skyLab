#pragma once

#include "GameOption.h"
#include "ISS.h"
#include "Debris.h"

class InGameEvent;
class Character;
class Dispenser;
class SpaceMine;

class ActorManager
{
public:
	ActorManager();
	virtual ~ActorManager();

	void Init( );

	virtual void BroadcastIssChange() = 0;
	virtual void BroadcastCharacterChange( int idx, ChangeType type ) = 0;
	virtual void BroadcastStructureInstallation( int structureId, StructureType structureType, D3DXVECTOR3 position, D3DXVECTOR3 direction, TeamColor teamColor ) = 0;
	virtual void BroadcastStructureUninstallation( int structureId, StructureType structureType ) = 0;
	virtual void BroadcastDispenserEffect( int idx, bool dispenserEffectFlag ) = 0;
	virtual void BroadcastDisasterOccurrence(D3DXVECTOR3 direction, float remainTime) = 0;
	virtual void BroadcastISSSkillResult(D3DXVECTOR3 direction, D3DXVECTOR3 position) = 0;
	
	// 	클라이언트 처음 접속하면 클라이언트 세션이 해당 플레이어의 액터-게임 캐릭터-를 등록한다.
	// 	클라이언트 세션의 멤버 액터의 포인터를 인자로 넣어서 등록하고,
	// 	매니저는 등록된 인덱스값을 actorId로 사용하도록 반환한다.
	int		RegisterCharacter( Character* newCharacter );

	void	DeregisterCharacter( int characterId );
	
	// update - 일단 가지고 있는 플레이어들 상태를 업데이트 한다.
	void Update();

	// 인자로 받은 id가 유효한지( list에 등록되어 있는지 ) 판정
	bool IsValidId( int characterId );
	
	// 입력된 아이디의 캐릭터가 바라보는 방향에 있는 캐릭터 중 가장 가까이 있는 캐릭터의 아이디를 반환	
	std::tuple<int, D3DXVECTOR3> DetectTarget( int characterId, const D3DXVECTOR3& direction );

	ISS* GetIss() { return &m_ISS; }

	int	InstallDispenser( const D3DXVECTOR3& position, const D3DXVECTOR3& direction, TeamColor team, int playerId );
	void UninstallDispenser( unsigned int targetId );

	int	InstallMine( const D3DXVECTOR3& position, const D3DXVECTOR3& direction, TeamColor team, int playerId );
	void UninstallMine( unsigned int targetId );

	// 현재 ISS 위치 및 속도 정보 리턴
	float GetIssPositionZ() { return m_ISS.GetPosition(); }
	float GetIssVelocityZ() { return m_ISS.GetVelocity(); }

	// 현재 ISS 각 모듈의 소유자 및 체력 정보 반환
	std::tuple<TeamColor, float> GetModuleState( int moduleIdx );

	const CollisionBox* GetModuleBoundingBox( int moduleIdx );

	const std::array<Debris*, RESOURCE_DEBRIS_NUMBER>& GetResourceDebrisList() const { return m_ResourceDebrisList; }
	void RemoveResourceDebris( int index );

	const std::array<Character*, REAL_PLAYER_NUM>& GetCharacterList() const { return m_CharacterList; }

	const std::map<unsigned, Dispenser*>& GetDispenserList() { return m_DispenserList; }
	const std::map<unsigned, SpaceMine*>& GetSpaceMineList() { return m_SpaceMineList; }

	void ClearPlayerStructureList( int playerId );

	// 입력받은 범위 안에 있는 캐릭터 id반환		
	std::vector<int> DetectTargetsInRange( int characterId, float range );
	
	// random Seed 반환
	int	 GetRandomSeed() { return m_RandomSeed; }

	int GetGatheredDebris() const { return m_GatheredDebris; }
	void SetGatheredDebris( int val ) { m_GatheredDebris = val; }

	InGameEvent* GetEvent() { return m_GameEvent; }
	void SetRandomEvent();

protected:
	// 지금은 싱글 스레드니까 락은 필요없다.
	// SRWLOCK m_SRWLock;

	void CheckCollision();

	DWORD m_PrevTime = 0;

	// 충돌한 아이들 저장하기 위한 변수
	std::set<int>						m_CollidedPlayers;
	std::set<int>						m_DeadPlayers;

	// player list
	std::array<Character*, REAL_PLAYER_NUM>	m_CharacterList;

	// teamList - playerId를 저장
	std::set<int> m_TeamBlue;
	std::set<int> m_TeamRed;

	InGameEvent*	m_GameEvent = nullptr;
	ISS				m_ISS;
	TeamColor		m_WinnerTeam = TeamColor::NO_TEAM;

	std::map<unsigned, Dispenser*>	m_DispenserList;
	unsigned int					m_DispensereId = 1; // 0은 없는 상태
	std::array<unsigned int, MAX_DISPENSER_NUMBER * REAL_PLAYER_NUM> m_DispenserSlot;

	std::map<unsigned, SpaceMine*>	m_SpaceMineList;
	unsigned int					m_SpaceMineId = 1; // 0은 없는 상태
	std::array<unsigned int, MAX_SPACE_MINE_NUMBER * REAL_PLAYER_NUM> m_SpaceMineSlot;

	bool m_GameEndFlag = false;

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