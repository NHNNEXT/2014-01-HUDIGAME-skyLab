#include "stdafx.h"

#include "ActorManager.h"
#include "Character.h"
#include "ObjectTable.h"

#include "Physics.h"
#include "GameData.h"
#include "Dispenser.h"
#include "SpaceMine.h"

ActorManager::ActorManager()
{
	m_CharacterList.fill( nullptr );
	m_ResourceDebrisList.fill( nullptr );
	m_GatheredDebrisList.fill( false );
}

ActorManager::~ActorManager()
{
	delete GObjectTable;

	for ( std::map<unsigned, SpaceMine*>::const_iterator it = m_SpaceMineList.begin(); it != m_SpaceMineList.end(); ++it )
	{
		delete it->second;
	}

	for ( std::map<unsigned, Dispenser*>::const_iterator it = m_DispenserList.begin(); it != m_DispenserList.end(); ++it )
	{
		delete it->second;
	}

	for ( auto iter : m_ResourceDebrisList )
	{
		delete iter;
		iter = nullptr;
	}
}

void ActorManager::Init( )
{
	// 시간 기반 random seed 생성
	srand( timeGetTime() );
	m_RandomSeed = rand();	

	g_GameData = GameData::Create();
	g_GameData->Init();

	m_PrevTime = timeGetTime( );

	m_Event.Init();

	m_ISS.Init();
	m_TeamBlue.clear();
	m_TeamRed.clear();

	m_CharacterList.fill( nullptr );

	GObjectTable = new ObjectTable;
	GObjectTable->Init( this );

	// random seed설정, client에서도 동일한 random시드로 자원 위치를 생성하기 위함
	srand( m_RandomSeed );
	for ( int i = 0; i < RESOURCE_DEBRIS_NUMBER; ++i )
	{
		Debris* newDebris = new Debris();
		newDebris->Init();
		m_ResourceDebrisList[i] = newDebris ;
	}

	m_WinnerTeam = TeamColor::NO_TEAM;

	m_GameEndFlag = false;

	// InitializeSRWLock( &m_SRWLock );
}

int ActorManager::RegisterCharacter( Character* newCharacter )
{
	// 일단 배열이 크지 않으므로 이렇게 가자
	for ( unsigned int characterId = 0; characterId < REAL_PLAYER_NUM; ++characterId )
	{
		if ( m_CharacterList[characterId] == nullptr )
		{
			m_CharacterList[characterId] = newCharacter;

			// 팀 추가 - 더 적은 팀에 배치
			if ( m_TeamBlue.size() < m_TeamRed.size() )
			{
				m_CharacterList[characterId]->SetTeam( TeamColor::BLUE );
				m_TeamBlue.insert( characterId );
			}
			else
			{
				m_CharacterList[characterId]->SetTeam( TeamColor::RED );
				m_TeamRed.insert( characterId );
			}

			GObjectTable->SetCharacter( newCharacter, characterId );

			return characterId;
		}
	}

	return -1; // 빈 자리가 없습니다.
}

void ActorManager::DeregisterCharacter( int characterId )
{
	assert( m_CharacterList[characterId] );

	// 일단 배치된 팀에서 빼자.
	m_TeamBlue.erase( characterId );
	m_TeamRed.erase( characterId );

	GObjectTable->SetCharacter( nullptr, characterId );

	// 객체의 삭제는 생성한 clientSession에서 한다
	// delete m_ActorList[actorId];
	m_CharacterList[characterId] = nullptr;

	// 만약 모든 플레이어가 나간 빈 방이 되면 게임 상태 초기화
	int currentPlayerNumber = 0;

	for ( unsigned int playerId = 0; playerId < REAL_PLAYER_NUM; ++playerId )
	{
		if ( m_CharacterList[playerId] != nullptr )
			++currentPlayerNumber;
	}

	if ( currentPlayerNumber == 0 )
		Init();
}

void ActorManager::Update( )
{
	DWORD currentTime = timeGetTime( );
	float dt = ( static_cast<float>( currentTime - m_PrevTime ) ) / 1000.f;
	m_PrevTime = currentTime;	

	for ( unsigned int actorId = 0; actorId < REAL_PLAYER_NUM; ++actorId )
	{
		if ( m_CharacterList[actorId] != nullptr )
		{
			m_CharacterList[actorId]->Update( dt );
			if ( !m_CharacterList[actorId]->GetClassComponent()->IsAlive() )
			{
				m_DeadPlayers.insert( actorId );
			}
		}
	}

	// 게임 내 재난 상황 이벤트 업데이트
	m_Event.Update( dt );

	// ISS 관련 업데이트
	m_ISS.Update( dt );

	float posIss = m_ISS.GetPosition();

	if ( posIss > WINNING_DISTANCE )
	{
		m_WinnerTeam = TeamColor::BLUE;
	}
	else if ( posIss < -WINNING_DISTANCE )
	{
		m_WinnerTeam = TeamColor::RED;
	}

	// 조심해!!
	// 네이밍 이상함
	std::vector<unsigned int> deleteMine;
	
	// space mine 업데이트
	for ( std::map<unsigned, SpaceMine*>::const_iterator it = m_SpaceMineList.begin( ); it != m_SpaceMineList.end( ); ++it )
	{
		SpaceMine* mine = it->second;

		// mine 위치 업데이트 필요
		// ISS에 설치 되므로 ISS의 이동에 영향을 받으므로 일단은 여기서 업데이트 한다
		mine->UpdateIssPosition( m_ISS.GetPosition() );

		if ( mine->React() )
		{
			deleteMine.push_back( it->first );
		}
	}

	// 레알 삭제
	std::for_each( deleteMine.begin(), deleteMine.end(), [&]( unsigned int each )
	{
		UninstallMine( each );
	}
	);

	// Dispenser update
	for ( std::map<unsigned, Dispenser*>::const_iterator it = m_DispenserList.begin(); it != m_DispenserList.end(); ++it )
	{
		Dispenser* dispenser = it->second;

		// 업데이트
		dispenser->UpdateIssPosition( m_ISS.GetPosition() );
		dispenser->Update( dt );
	}

	// 충돌 체크
	CheckCollision();
}

bool ActorManager::IsValidId( int characterId )
{
	if ( m_CharacterList[characterId] != nullptr )
		return true;

	return false;
}

void ActorManager::CheckCollision()
{
	// 순회하면서 각 액터들이 충돌하는지 확인
	// 충돌하는 애들 있으면 각각에게 충돌 판정을 전달한다.
	// 전달 방식은 충돌 후 이동 방향(서로 반대 방향)을 전달한다.
	for ( int i = 0; i < REAL_PLAYER_NUM; ++i )
	{
		// 조심해!!
		// 일단 지금은 항상 움직이는 상태...
		// 움직임이 있는 애들만 체크
		if ( m_CharacterList[i] == nullptr || !m_CharacterList[i]->IsMoving() )
			continue;

		const CollisionBox* boxI = m_CharacterList[i]->GetCollisionBox();
		const CollisionBox* boxJ = nullptr;

		// ISS와의 충돌 확인
		for ( int j = 0; j < MODULE_NUMBER; ++j )
		{
			// 각각의 모듈의 충돌 박스를 가져온다.
			boxJ = m_ISS.GetModuleCollisionBox( j );

			// 멀면 확인 안 함
			D3DXVECTOR3 collisionDirection = boxJ->m_CenterPos - boxI->m_CenterPos;
			if ( D3DXVec3Length( &collisionDirection ) > boxI->m_Radius + boxJ->m_Radius )
				continue;

			if ( Physics::IsCollide( boxI, boxJ ) )
			{
				// 상대 속도가 서로 멀어지는 방향이라면 확인 안 함
				// D3DXVECTOR3 relativeVelocity = D3DXVECTOR3( 0.0f, 0.0f, m_ISS.GetVelocity() ) - m_CharacterList[i]->GetVelocity();
				D3DXVECTOR3 relativeVelocity = m_CharacterList[i]->GetVelocity() - D3DXVECTOR3( 0.0f, 0.0f, m_ISS.GetVelocity() );
				if ( D3DXVec3Dot( &relativeVelocity, &collisionDirection ) < 0 )
					return;

				// 이 경우에는 ISS는 그대로 있고 플레이어만 튕긴다.
				// 우선 운동 방향을 구하고
				D3DXVec3Normalize( &collisionDirection, &m_CharacterList[i]->GetVelocity() );

				// 충돌면의 수직 벡터를 구한 뒤
				D3DXVECTOR3 normalVec( ZERO_VECTOR3 );
				Physics::IntersectionCheckRayBox( nullptr, nullptr, &normalVec, collisionDirection, m_CharacterList[i]->GetTransform()->GetPosition(), boxJ );

				// 두 벡터를 이용해서 반사 벡터를 구하고
				D3DXVECTOR3 reflectionVec = Physics::GetReflectionVector( collisionDirection, normalVec );

				// 원래 운동 속도의 크기로 반사벡터 방향으로 속도를 바꾼다
				m_CharacterList[i]->SetVelocity( reflectionVec * D3DXVec3Length( &m_CharacterList[i]->GetVelocity() ) );

				// ISS와 충돌한 플레이어의 아이디를 추가한다.
				m_CollidedPlayers.insert( i );
			}
		}

		// 플레이어간 충돌 체크
		for ( int j = i + 1; j < REAL_PLAYER_NUM; ++j )
		{
			if ( m_CharacterList[j] == nullptr )
				continue;

			boxJ = m_CharacterList[j]->GetCollisionBox();

			// 두 점의 거리가 멀면 체크 안 함
			D3DXVECTOR3 collisionDirection = m_CharacterList[j]->GetTransform()->GetPosition() - m_CharacterList[i]->GetTransform()->GetPosition();
			// printf_s( "%f / %f\n", D3DXVec3Length( &collisionDirection ), m_ActorList[i]->GetCollisionBox().m_Radius + m_ActorList[j]->GetCollisionBox().m_Radius );
			if ( D3DXVec3Length( &collisionDirection ) > boxI->m_Radius + boxJ->m_Radius )
				continue;

			// 충돌체크
			if ( Physics::IsCollide( boxI, boxJ ) )
			// if ( m_ActorList[i]->GetCollisionBox() & m_ActorList[j]->GetCollisionBox() )
			{
				// 두 물체의 중심점을 잇는 단위 벡터 생성
				D3DXVec3Normalize( &collisionDirection, &collisionDirection );

				// 충돌 체크가 충돌하는 시점에 정확하게 계산하는 것이 아님
				// 이미 충돌이 일어나고 조금의 시점이 지난 상태에서 확인하므로 결국 두 물체는 조금 겹쳐져 있는 상태
				// 그 상태에서 운동량에 변화를 주어 서로 반대 방향으로 밀어내면 다음 프레임에서
				// 아직 충돌 상태에서 벗어나지 못한 상태로 다시 충돌 판정을 하게 되고 서로의 운동량을 다시 바꾸게 됨
				// 결국 물체는 다시 가까워지는 방향으로 운동량이 변하게 되고, 서로 떨어지지 못한 채 계속 충돌 판정을 받게 됨
				// 그래서 두 물체의 운동 상태가 서로에게서 멀어지고 있는 중이라면 충돌에 의한 운동량 변화를 적용하지 않음
				// D3DXVECTOR3 relativeVelocity = m_CharacterList[j]->GetVelocity() - m_CharacterList[i]->GetVelocity();
				D3DXVECTOR3 relativeVelocity = m_CharacterList[i]->GetVelocity() - m_CharacterList[j]->GetVelocity();
				if ( D3DXVec3Dot( &relativeVelocity, &collisionDirection ) < 0 )
					return;

				float iMass = m_CharacterList[i]->GetMass();
				float jMass = m_CharacterList[j]->GetMass();

				float iVelocity = D3DXVec3Dot( &( m_CharacterList[i]->GetVelocity() ), &collisionDirection );
				float jVelocity = D3DXVec3Dot( &( m_CharacterList[j]->GetVelocity() ), &collisionDirection );
				
				// 질량에 비례해서 운동 상태 변경
				m_CharacterList[i]->IncreaseVelocity(
					( 2 * jMass / ( iMass + jMass ) )
					* ( jVelocity - iVelocity ) * collisionDirection
					);

				m_CharacterList[j]->IncreaseVelocity(
					( 2 * iMass / ( iMass + jMass ) )
					* ( iVelocity - jVelocity ) * collisionDirection
					);

				// 충돌한 플레이어의 아이디를 추가한다.
				m_CollidedPlayers.insert( i );
				m_CollidedPlayers.insert( j );
			}
		}
	}
}

std::tuple<int, D3DXVECTOR3> ActorManager::DetectTarget( int characterId, const D3DXVECTOR3& direction )
{
	// 충돌 박스의 각 점들을 조합해서 만들 수 있는 면 6개에 대해서
	// 요청한 액터의 뷰( z축 ) 방향과 각각의 면이 교차하는지 확인한다.
	float currentDistance = std::numeric_limits<float>::infinity();
	int targetId = -1;
	
	D3DXVECTOR3 spinAxis( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 viewDirection = m_CharacterList[characterId]->GetViewDirection( direction );
	D3DXVECTOR3	startPoint = m_CharacterList[characterId]->GetTransform()->GetPosition();
	
	for ( int i = 0; i < REAL_PLAYER_NUM; ++i )
	{
		if ( i == characterId || m_CharacterList[i] == nullptr )
			continue;

		D3DXVECTOR3 tempAxis( 0.0f, 0.0f, 0.0f );
		
		float tempDistance = std::numeric_limits<float>::infinity();
		if ( Physics::IntersectionCheckRayBox( &tempAxis, &tempDistance, nullptr, viewDirection, startPoint, m_CharacterList[i]->GetCollisionBox() ) )
		{
			// 거리 구해서 더 짧으면 인덱스 업데이트
			// 정확하게는 두 물체의 기준점 사이의 거리를 비교하는 것이 아니라 교차점과 스킬을 사용한 객체의 기준점의 거리를 구해서 비교해야 함
			if ( tempDistance < currentDistance && tempDistance < SKILL_RANGE )
			{
				currentDistance = tempDistance;
				spinAxis = tempAxis;
				targetId = i;
			}
		}
	}

	return std::tuple<int, D3DXVECTOR3>( targetId, spinAxis );
}

std::vector<int> ActorManager::DetectTargetsInRange( int characterId, float range )
{
	std::vector<int> targets;

	for ( int i = 0; i < REAL_PLAYER_NUM; ++i )
	{
		if ( i == characterId || m_CharacterList[i] == nullptr )
			continue;

		float distance = D3DXVec3Length( &D3DXVECTOR3(m_CharacterList[i]->GetTransform()->GetPosition() - m_CharacterList[characterId]->GetTransform()->GetPosition() ) );

		if ( range > distance )
			targets.push_back( i );
	}

	return targets;
}

int	ActorManager::InstallDispenser( const D3DXVECTOR3& position, const D3DXVECTOR3& direction, TeamColor team )
{
 	Dispenser* newDispenser = new Dispenser( m_DispensereId, team, m_ISS.GetPosition() );

	newDispenser->GetTransform()->SetPosition( position );
	newDispenser->GetTransform()->SetRotation( direction );

	m_DispenserList.insert( std::map<unsigned int, Dispenser*>::value_type( m_DispensereId, newDispenser ) );

	// 설치 방송
	BroadcastStructureInstallation( m_DispensereId, StructureType::DISPENSER, position, direction, team );

	return m_SpaceMineId++;
}

void ActorManager::UninstallDispenser( unsigned int targetId )
{
	std::map<unsigned, Dispenser*>::iterator it = m_DispenserList.find( targetId );
	assert( it != m_DispenserList.end() );

	// 설치 해제 방송
	BroadcastStructureUninstallation( m_DispensereId, StructureType::DISPENSER );

	delete it->second;
	m_DispenserList.erase( targetId );
}

int	ActorManager::InstallMine( const D3DXVECTOR3& position, const D3DXVECTOR3& direction, TeamColor team )
{
	SpaceMine* newMine = new SpaceMine( m_SpaceMineId, team, m_ISS.GetPosition() );

	newMine->GetTransform()->SetPosition( position );
	newMine->GetTransform()->SetRotation( direction );
	
	m_SpaceMineList.insert( std::map<unsigned int, SpaceMine*>::value_type( m_SpaceMineId, newMine ) );

	// 설치 방송
	BroadcastStructureInstallation( m_SpaceMineId, StructureType::SPACE_MINE, position, direction, team );

	return m_SpaceMineId++;
}

void ActorManager::UninstallMine( unsigned int targetId )
{
	std::map<unsigned, SpaceMine*>::iterator it = m_SpaceMineList.find( targetId );
	assert( it != m_SpaceMineList.end() );

	// 설치 해제 방송
	BroadcastStructureUninstallation( m_SpaceMineId, StructureType::SPACE_MINE );

	delete it->second;
	m_SpaceMineList.erase( targetId );
}

std::tuple<TeamColor, float> ActorManager::GetModuleState( int moduleIdx )
{
	return m_ISS.GetModuleState( moduleIdx );
}

const CollisionBox* ActorManager::GetModuleBoundingBox( int moduleIdx )
{ 
	return m_ISS.GetModuleCollisionBox( moduleIdx ); 
}

void ActorManager::RemoveResourceDebris( int index )
{
	if ( m_ResourceDebrisList[index] != nullptr )
	{
		delete m_ResourceDebrisList[index];
		m_ResourceDebrisList[index] = nullptr;
	}
}
