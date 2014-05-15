#include "stdafx.h"
#include "ISS.h"

#include "Physics.h"

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
}

void ISS::UpdateItSelf( float dTime )
{
	// 점령 상태 확인
	// 점령 상태에 따라서 현재 위치 이동
	// 자신의 위치에 따라서 m_Matrix 업데이트

	D3DXVECTOR3 tmpVec3 = GetTransform()->GetPosition();
	Physics::CalcCurrentPosition( &tmpVec3, m_CharacterClass->GetVelocity(), dTime );
	GetTransform()->SetPosition( tmpVec3 );

	// m_Matrix에 결과 저장
	D3DXQUATERNION	qRotation;
	D3DXQuaternionRotationYawPitchRoll( &qRotation, D3DXToRadian( GetTransform()->GetRotationY() ), D3DXToRadian( GetTransform()->GetRotationX() ), D3DXToRadian( GetTransform()->GetRotationZ() ) );
	D3DXMatrixTransformation( &m_Matrix, NULL, NULL, &GetTransform()->GetScale(), NULL, &qRotation, &GetTransform()->GetPosition() );

	// 조심해!!
	// 나중에 ISSModule이 ISS의 m_Matrix를 참조할 수 있도록 변경할 것
	std::for_each( m_ModuleList.begin(), m_ModuleList.end(),
		[&]( ISSModule &eachModule )
	{
		eachModule.SetMatrix( m_Matrix );
	}
	);
}

std::tuple<ISSModuleName, TeamColor, float, float> ISS::Occupy( const D3DXVECTOR3 &viewDirection, const D3DXVECTOR3 &startPoint, TeamColor callerColor )
{
	float currentDistance = std::numeric_limits<float>::infinity();
	ISSModuleName targetModule = ISSModuleName::NO_MODULE;

	// 자신에게 등록된 모듈들을 차례대로 돌면서 
	// 유저의 position 에서 viewDirection 방향의 ray를 쏴서 걸리는 점령 포인트가 있는지 확인 - 거리도 포함해서 계산

	std::for_each( m_ModuleList.begin(), m_ModuleList.end(),
		[&]( ISSModule &eachModule )
	{
		float tempDistance = std::numeric_limits<float>::infinity();
		if ( Physics::IntersectionCheckRayBox( nullptr, &tempDistance, viewDirection, startPoint, eachModule.GetControlPointBox() ) )
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

	// 걸리는 애가 있으면 그 모듈의 상태를 바꾸고 변화가 적용된 모듈 id와 점령 상태 반환
	if ( targetModule != ISSModuleName::NO_MODULE )
	{
		// 점령 상태 전환
		m_ModuleList[static_cast<int>( targetModule )].Occupy( callerColor );

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
		m_CharacterClass->SetVelocity( D3DXVECTOR3( .0f, .0f, (blueCount - redCount) * ISS_MOVE_WEIGHT ) );

		return std::make_tuple( targetModule, m_ModuleList[static_cast<int>( targetModule )].GetOwner(), GetTransform()->GetPositionZ(), m_CharacterClass->GetVelocity().z );
	}

	return std::make_tuple( ISSModuleName::NO_MODULE, TeamColor::NO_TEAM, 0.0f, 0.0f );
}

std::tuple<ISSModuleName, float> ISS::Destroy( const D3DXVECTOR3 &viewDirection, const D3DXVECTOR3 &startPoint )
{
	float currentDistance = std::numeric_limits<float>::infinity();
	ISSModuleName targetModule = ISSModuleName::NO_MODULE;

	// 자신에게 등록된 모듈들을 차례대로 돌면서 
	// 유저의 position 에서 viewDirection 방향의 ray를 쏴서 걸리는 모듈이 있는지 확인 - 거리도 포함해서 계산
	std::for_each( m_ModuleList.begin(), m_ModuleList.end(),
		[&]( ISSModule &eachModule )
	{
		// intersection 확인
		float tempDistance = std::numeric_limits<float>::infinity();
		if ( Physics::IntersectionCheckRayBox( nullptr, &tempDistance, viewDirection, startPoint, eachModule.GetCollisionBox() ) )
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

	// 걸리는 애가 있으면 체력을 낮추고 걸린 모듈의 id와 변경된 체력을 tuple에 담아서 리턴
	if ( targetModule != ISSModuleName::NO_MODULE )
	{
		// 캐스팅을 쓰는 건 안 좋은 것 같은데, 자료구조를 맵으로 바꿔야하나...
		///# 당연히 구조적으로 별로다.. 모듈 리스트의 인덱스와 모듈 이름이 상호 호환되게 하는게 좋음
		///# 그게 힘들면 Name to Module Convertor라고 만들던가..

		return std::make_tuple( targetModule, m_ModuleList[static_cast<int>(targetModule)].DecreaseHP() );
	}

	return std::make_tuple( ISSModuleName::NO_MODULE, 0.0f );
}

std::tuple<TeamColor, float> ISS::GetModuleState( int moduleIdx )
{
	return std::make_tuple( m_ModuleList[moduleIdx].GetOwner(), m_ModuleList[moduleIdx].GetHP() );
}