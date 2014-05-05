#include "stdafx.h"
#include "ActorManager.h"

#include "Physics.h"

// using Physics::operator&;

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
	m_ISS.Init();
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

/*
사용 안 함 - 클래스를 바꾸면 각 세션이 자신의 멤버 함수의 m_Character의 class component를 바꾸는 걸로 
결국 actorManager에 등록된 actor의 포인터는 그대로 유지되고, 내부 클래스만 바뀜
void ActorManager::ChangeActor( Actor* newActor, int actorId )
{
	// 다른 세션 캐릭터를 바꾸는 일은 없도록 만들어야 할 듯

	// 확인을 위해서는 함수 호출한 세션의 캐릭터가 삭제하려는 캐릭터와 같은지 확인 필요
	// 모든 인자를 호출하는 쪽에서 넣으므로 이 함수 안에서 확인은 힘들어 보임
	// actorManager가 유저들의 actor를 직접 가지지 않고 유저 포인터만 들고 있으면서 
	// 유저를 통해서 참조하면 각 유저가 자신의 캐릭터만 바꿀 수 있으니 괜찮겠지만...
	
	// 현재 구조에서는 이 함수를 호출하는 함수를 각 actor의 멤버 함수로 제한하고, 그 함수 안에서 자신의 actorId로 인자를 고정하도록 구현

	// 기존 캐릭터 삭제 -> 새로운 캐릭터 등록
	DeleteActor( actorId );
	m_ActorList[actorId] = newActor;
}
*/

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

	m_ISS.Update( dt );

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
	bool returnVal = false; // 충돌이 있는지 알려줌 - 클라이언트들에게 업데이트하라고 시켜야 되니까

	// 순회하면서 각 액터들이 충돌하는지 확인
	// 충돌하는 애들 있으면 각각에게 충돌 판정을 전달한다.
	// 전달 방식은 충돌 후 이동 방향(서로 반대 방향)을 전달한다.
	for ( int i = 0; i < MAX_PLAYER_NUM; ++i )
	{
		// 조심해!!
		// 일단 지금은 항상 움직이는 상태...
		// 움직임이 있는 애들만 체크
		if ( m_ActorList[i] == nullptr || !m_ActorList[i]->IsMoving( ) )
			continue;

		const CollisionBox* boxI = m_ActorList[i]->GetCollisionBox();
		const CollisionBox* boxJ = nullptr;

		// ISS와의 충돌 확인
		for ( int j = 0; j < MODULE_NUMBER; ++j )
		{
			// 각각의 모듈의 충돌 박스를 가져온다.
			boxJ = m_ISS.GetModuleCollisionBox( j );

			D3DXVECTOR3 collisionDirection = boxJ->m_CenterPos - m_ActorList[i]->GetPosition();
			if ( D3DXVec3Length( &collisionDirection ) > boxI->m_Radius + boxJ->m_Radius )
				// continue;

			// 충돌체크 - 주석은 아래 플레이어간 충돌 참조
			if ( Physics::IsCollide( boxI, boxJ ) )
			{
				// 이 경우에는 ISS는 그대로 있고 플레이어만 튕긴다.
				D3DXVec3Normalize( &collisionDirection, &collisionDirection );

				D3DXVECTOR3 relativeVelocity = -m_ActorList[i]->GetVelocity();
				if ( D3DXVec3Dot( &relativeVelocity, &collisionDirection ) > 0 )
				{
					return false;
				}

				// 조심해!!
				// 반사되지 않고 입사각의 반대로 튕기고 있다.
				m_ActorList[i]->IncreaseVelocity( relativeVelocity * 2.0f );

				returnVal = true;
			}
		}


		// 플레이어간 충돌 체크
		for ( int j = i + 1; j < MAX_PLAYER_NUM; ++j )
		{
			if ( m_ActorList[j] == nullptr )
				continue;

			boxJ = m_ActorList[j]->GetCollisionBox();

			// 두 점의 거리가 가까우면 체크 안 함
			D3DXVECTOR3 collisionDirection = m_ActorList[j]->GetPosition() - m_ActorList[i]->GetPosition();
			// printf_s( "%f / %f\n", D3DXVec3Length( &collisionDirection ), m_ActorList[i]->GetCollisionBox().m_Radius + m_ActorList[j]->GetCollisionBox().m_Radius );
			if ( D3DXVec3Length( &collisionDirection ) > boxI->m_Radius + boxJ->m_Radius )
				continue;

			// 충돌체크
			if ( Physics::IsCollide( boxI, boxJ ) )
			// if ( m_ActorList[i]->GetCollisionBox() & m_ActorList[j]->GetCollisionBox() )
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

				m_CrashedPlayers = std::make_tuple( i, j );

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
		float tempDistance = static_cast<float>( HUGE );
		if ( Physics::IntersectionCheckRayBox( &tempAxis, &tempDistance, viewDirection, startPoint, m_ActorList[i]->GetCollisionBox() ) )
		{
			// 거리 구해서 더 짧으면 인덱스 업데이트
			// 정확하게는 두 물체의 기준점 사이의 거리를 비교하는 것이 아니라 교차점과 스킬을 사용한 객체의 기준점의 거리를 구해서 비교해야 함
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
