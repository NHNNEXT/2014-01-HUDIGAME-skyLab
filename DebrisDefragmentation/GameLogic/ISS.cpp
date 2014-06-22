#include "stdafx.h"
#include "ISS.h"

#include "Physics.h"
#include "ObjectTable.h"
#include "ActorManager.h"

ISS::ISS()
{
}


ISS::~ISS()
{
}

void ISS::Init()
{
	// 각각의 모듈을 초기화
	for ( int i = 0; i < MODULE_NUMBER; ++i )
	{
		m_ModuleList[i].Init( static_cast<ISSModuleName>( i ) );
	}

	m_CurrentPos = 0.0f;
	m_Velocity = 0.0f;
}

void ISS::Update( float dTime )
{
	// 현재 속도로 이동해서 현재 위치 계산 - 기존 속도 공식을 이용하기 위해서 벡터로 변환해서 계산
	D3DXVECTOR3 currentPos( 0.0f, 0.0f, m_CurrentPos );
	Physics::CalcCurrentPosition( &currentPos, D3DXVECTOR3( 0.0f, 0.0f, m_Velocity ), dTime );
	m_CurrentPos = currentPos.z;

	// 조심해!!
	// 나중에 ISSModule이 ISS의 m_Matrix를 참조할 수 있도록 변경할 것
	///# std::array 순회하면서 처리할 때... 어떤 곳에서는 람다를 주로 쓰고 어떤 곳에서는 for루프로 일일이 처리하고... 통일좀 하삼.
	// 팀 컨벤션 표준 지정 회의 중입니다. ㅠ
	std::for_each( m_ModuleList.begin(), m_ModuleList.end(), [&]( ISSModule &eachModule )
	{
		eachModule.SetISSPos( m_CurrentPos );
		eachModule.Update( dTime );
	}
	);
}

ISSModule* ISS::GetModule( ISSModuleName moduleName )
{ 
	if ( moduleName == ISSModuleName::NO_MODULE )
		return nullptr;

	return &m_ModuleList[static_cast<int>( moduleName )];
}

bool ISS::Occupy( int characterId, D3DXVECTOR3 direction )
{
	Character* skillUserCharacter = GObjectTable->GetCharacter( characterId );
	assert( skillUserCharacter );

	ISSModuleName targetModuleName = ModuleOnRay( skillUserCharacter->GetViewDirection( direction ), skillUserCharacter->GetTransform()->GetPosition() );

	// 걸리는 애가 있으면 그 모듈의 상태를 바꾸고 변화가 적용된 모듈 id와 점령 상태 반환
	if ( targetModuleName != ISSModuleName::NO_MODULE )
	{
		// 점령 상태 전환
		m_ModuleList[static_cast<int>( targetModuleName )].Occupy( skillUserCharacter->GetTeam() );

		// 운동 상태 변경
		int blueCount = 0;
		int redCount = 0;

		std::for_each( m_ModuleList.begin(), m_ModuleList.end(),
			[&]( const ISSModule &eachModule )
		{
			switch ( eachModule.GetOwner() )
			{
			case TeamColor::BLUE:
				++blueCount;
				break;
			case TeamColor::RED:
				++redCount;
				break;
			default:
				break;
			}
		}
		);

		// 이동
		//m_RigidBody.m_Velocity.z = ( ( blueCount - redCount ) * ISS_MOVE_WEIGHT );
		m_Velocity = ( blueCount - redCount ) * ISS_MOVE_WEIGHT;

		GObjectTable->GetActorManager()->BroadcastIssChange();

		// 조심해!!
		// 여기부턴 destroy껏과 중복코드 ㅠㅠ, 일단 하드코딩 ㄱㄱ
		D3DXVECTOR3 characterPosition = skillUserCharacter->GetTransform()->GetPosition();
		D3DXVECTOR3	skillDirection = skillUserCharacter->GetViewDirection( direction );
		D3DXVec3Normalize( &skillDirection, &skillDirection );

		ISSModule* targetModule = GObjectTable->GetActorManager()->GetIss()->GetModule( targetModuleName );
		float distance = std::numeric_limits<float>::infinity();

		if ( !Physics::IntersectionCheckRayBox( nullptr, &distance, nullptr, skillDirection, characterPosition, targetModule->GetCollisionBox() ) )
			return false;

		GObjectTable->GetActorManager()->BroadcastISSSkillResult( ZERO_VECTOR3, characterPosition + skillDirection * distance );
		return true;
	}

	return false;
}

bool ISS::Destroy( int characterId, D3DXVECTOR3 direction )
{
	Character* skillUserCharacter = GObjectTable->GetCharacter( characterId );
	assert( skillUserCharacter );

	D3DXVECTOR3 characterPosition = skillUserCharacter->GetTransform()->GetPosition();
	D3DXVECTOR3	skillDirection = skillUserCharacter->GetViewDirection( direction );
	D3DXVec3Normalize( &skillDirection, &skillDirection );

	ISSModuleName targetModuleName = ModuleOnRay( skillDirection, characterPosition );

	if ( targetModuleName == ISSModuleName::NO_MODULE )
		return false;
	
	m_ModuleList[static_cast<int>( targetModuleName )].DecreaseHP();

	// 방송할 것
	GObjectTable->GetActorManager()->BroadcastIssChange();

	// 공격한 모듈에 대한 방향과 그 위치를 방송
	ISSModule* targetModule = GObjectTable->GetActorManager()->GetIss()->GetModule( targetModuleName );
	float distance = std::numeric_limits<float>::infinity();
	
	if ( !Physics::IntersectionCheckRayBox( nullptr, &distance, nullptr, skillDirection, characterPosition, targetModule->GetCollisionBox() ) )
 		return false;
		
	GObjectTable->GetActorManager()->BroadcastISSSkillResult( skillDirection, characterPosition + skillDirection * distance );
	return true;
}

ISSModuleName ISS::ModuleOnRay( const D3DXVECTOR3 &viewDirection, const D3DXVECTOR3 &startPoint )
{
	float currentDistance = std::numeric_limits<float>::infinity();
	ISSModuleName targetModule = ISSModuleName::NO_MODULE;

	// 자신에게 등록된 모듈들을 차례대로 돌면서 
	// 유저의 position 에서 viewDirection 방향의 ray를 쏴서 걸리는 모듈이 있는지 확인 - 거리도 포함해서 계산
	std::for_each( m_ModuleList.begin(), m_ModuleList.end(), [&]( ISSModule &eachModule )
	{
		// intersection 확인
		float tempDistance = std::numeric_limits<float>::infinity();
		if ( Physics::IntersectionCheckRayBox( nullptr, &tempDistance, nullptr, viewDirection, startPoint, eachModule.GetCollisionBox() ) )
		{
			// 조심해!
			// 스킬 사용 범위가 정해지면 그것과 비교해서 더 먼 애는 제외
			// 더 가까운 애로 교체
			if ( tempDistance < currentDistance && tempDistance < SKILL_RANGE )
			{
				currentDistance = tempDistance;
				targetModule = eachModule.GetModuleName();
			}
		}
	}
	);

	return targetModule;
}

std::tuple<TeamColor, float> ISS::GetModuleState( int moduleIdx )
{
	return std::make_tuple( m_ModuleList[moduleIdx].GetOwner(), m_ModuleList[moduleIdx].GetHP() );
}