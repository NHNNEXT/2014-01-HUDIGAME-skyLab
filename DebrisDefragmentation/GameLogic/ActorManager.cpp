#include "stdafx.h"
#include "ActorManager.h"
#include "Physics.h"

using Physics::operator&;

ActorManager::ActorManager()
{
	for ( unsigned int playerId = 0; playerId < MAX_PLAYER_NUM; ++playerId )
	{
		m_ActorList[playerId] = nullptr;
	}
}


ActorManager::~ActorManager()
{
}

void ActorManager::Init( )
{
	m_PrevTime = timeGetTime( );
	// InitializeSRWLock( &m_SRWLock );
}

int ActorManager::RegisterUser( Actor* newActor )
{
	// user id를 manager에 등록된 actor index와 같게 유지하면 객체들 인터랙션을 처리할 때 유리할 것 같은데
	// 어떻게 효율적으로 비어있는 index를 찾고 그걸 세션에게 할당할 지 잘 모르겠네요
	// 일단 이렇게 처음부터 순회하면서 비어있는 자리가 있으면 거기에 포인터 등록하고 idx 반환하도록 하는데...

	///# 배열의 크기가 크지 않으면 아래처럼 해도 됨. 커지면 아래처럼 하면 안되고 free-pool을 만들어 유지해야 함. ObjectPool<> 참고.
	for ( unsigned int actorId = 0; actorId < MAX_PLAYER_NUM; ++actorId )
	{
		if ( m_ActorList[actorId] == nullptr )
		{
			m_ActorList[actorId] = newActor;
			return actorId;
		}
	}

	return -1; // 빈 자리가 없습니다.
}

void ActorManager::ChangeActor( Actor* newActor, int actorId )
{
	// 다른 세션 캐릭터를 바꾸는 일은 없도록 만들어야 할 듯 ///# 그러면 체크하는 로직 넣어야지?
	// 확인을 위해서는 함수 호출한 세션의 캐릭터가 삭제하려는 캐릭터와 같은지 확인 필요

	// 기존 캐릭터 삭제 -> 새로운 캐릭터 등록
	DeleteActor( actorId );
	m_ActorList[actorId] = newActor;
}

void ActorManager::DeleteActor( int actorId )
{
	if ( m_ActorList[actorId] != nullptr )
	{
		// 객체의 삭제는 생성한 clientSession에서 한다
		// delete m_ActorList[actorId];
		m_ActorList[actorId] = nullptr;
	}
}

bool ActorManager::Update( )
{
	DWORD currentTime = timeGetTime( );
	float dt = ( static_cast<float>( currentTime - m_PrevTime ) ) / 1000.f;
	m_PrevTime = currentTime;

	for ( unsigned int actorId = 0; actorId < MAX_PLAYER_NUM; ++actorId )
	{
		if ( m_ActorList[actorId] != nullptr )
		{
			m_ActorList[actorId]->Update( dt );
		}
	}

	// 충돌 체크
	return CheckCollision();
}

bool ActorManager::IsValidId( int actorId )
{
	if ( m_ActorList[actorId] != nullptr )
		return true;

	return false;
}

bool ActorManager::CheckCollision()
{
	///# 그러니까.. 매 업데이트마다 모든 액터를 돌면서 서로 n * n-1 만큼 충돌 체크??
	///# 액터의 수가 많지 않으니까.. 이렇게 해도 되지만.. 원칙적으로는 이렇게 하면 안됨.. delta 가 있는 애들만.. 

	bool returnVal = false; // 충돌이 있는지 알려줌 - 클라이언트들에게 업데이트하라고 시켜야 되니까

	// 순회하면서 각 액터들이 충돌하는지 확인
	// 충돌하는 애들 있으면 각각에게 충돌 판정을 전달한다.
	// 전달 방식은 충돌 후 이동 방향(서로 반대 방향)을 전달한다.
	for ( int i = 0; i < MAX_PLAYER_NUM; ++i )
	{
		if ( m_ActorList[i] == nullptr )
			continue;

		for ( int j = i + 1; j < MAX_PLAYER_NUM; ++j )
		{
			if ( m_ActorList[j] == nullptr )
				continue;

			// 두 점의 거리가 가까우면 체크 안 함
			D3DXVECTOR3 collisionDirection = m_ActorList[j]->GetPosition() - m_ActorList[i]->GetPosition();
			// printf_s( "%f / %f\n", D3DXVec3Length( &collisionDirection ), m_ActorList[i]->GetCollisionBox().m_Radius + m_ActorList[j]->GetCollisionBox().m_Radius );
			if ( D3DXVec3Length( &collisionDirection ) > m_ActorList[i]->GetCollisionBox().m_Radius + m_ActorList[j]->GetCollisionBox().m_Radius )
				continue;

			// 충돌체크
			// if ( Physics::IsCollide( m_ActorList[i]->GetCollisionBox(), m_ActorList[j]->GetCollisionBox() ) )
			if (m_ActorList[i]->GetCollisionBox() & m_ActorList[j]->GetCollisionBox() )
			{
				printf_s( "collision!\n" );
				// 두 물체의 중심점을 잇는 단위 벡터 생성
				D3DXVec3Normalize( &collisionDirection, &collisionDirection );

				// 충돌 체크가 충돌하는 시점에 정확하게 계산하는 것이 아님
				// 이미 충돌이 일어나고 조금의 시점이 지난 상태에서 확인하므로 결국 두 물체는 조금 겹쳐져 있는 상태
				// 그 상태에서 운동량에 변화를 주어 서로 반대 방향으로 밀어내면 다음 프레임에서
				// 아직 충돌 상태에서 벗어나지 못한 상태로 다시 충돌 판정을 하게 되고 서로의 운동량을 다시 바꾸게 됨
				// 결국 물체는 다시 가까워지는 방향으로 운동량이 변하게 되고, 서로 떨어지지 못한 채 계속 충돌 판정을 받게 됨
				// 그래서 두 물체의 운동 상태가 서로에게서 멀어지고 있는 중이라면 충돌에 의한 운동량 변화를 적용하지 않음
				D3DXVECTOR3 relativeVelocity = m_ActorList[j]->GetVelocity() - m_ActorList[i]->GetVelocity();
				if ( D3DXVec3Dot( &relativeVelocity, &collisionDirection ) > 0 )
				{
					return false;
				}


				float iMass = m_ActorList[i]->GetMass();
				float jMass = m_ActorList[j]->GetMass();

				float iVelocity = D3DXVec3Dot( &( m_ActorList[i]->GetVelocity() ), &collisionDirection );
				float jVelocity = D3DXVec3Dot( &( m_ActorList[j]->GetVelocity() ), &collisionDirection );
				
				// 질량에 비례해서 운동 상태 변경
				m_ActorList[i]->IncreaseVelocity( 
					( 2 * jMass / ( iMass + jMass ) )
					* ( jVelocity - iVelocity ) * collisionDirection
					);

				m_ActorList[j]->IncreaseVelocity(
					( 2 * iMass / ( iMass + jMass ) )
					* ( iVelocity - jVelocity ) * collisionDirection
					);

				returnVal = true;
			}
		}
	}

	return returnVal;
}

std::tuple<int, D3DXVECTOR3> ActorManager::DetectTarget( int actorId, float x, float y, float z )
{
	// 충돌 박스의 각 점들을 조합해서 만들 수 있는 면 6개에 대해서
	// 요청한 액터의 뷰( z축 ) 방향과 각각의 면이 교차하는지 확인한다.
	float currentDistance = static_cast<float>( HUGE );
	int targetId = -1;
	
	D3DXVECTOR3 spinAxis( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 viewDirection = m_ActorList[actorId]->GetViewDirection( x, y, z );
	D3DXVECTOR3	startPoint = m_ActorList[actorId]->GetPosition();
	
	for ( int i = 0; i < MAX_PLAYER_NUM; ++i )
	{
		if ( i == actorId || m_ActorList[i] == nullptr )
			continue;

		D3DXVECTOR3 tempAxis( 0.0f, 0.0f, 0.0f );
		if ( Physics::IntersectionCheckRayBox( &tempAxis, viewDirection, startPoint, m_ActorList[i]->GetCollisionBox() ) )
		{
			// 거리 구해서 더 짧으면 인덱스 업데이트
			float tempDistance = D3DXVec3Length( &( startPoint - m_ActorList[i]->GetPosition() ) );
			if ( tempDistance < currentDistance )
			{
				currentDistance = tempDistance;
				spinAxis = tempAxis;
				targetId = i;
			}
		}
	}

	return std::tuple<int, D3DXVECTOR3>( targetId, spinAxis );
}
