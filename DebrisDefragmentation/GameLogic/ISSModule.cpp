#include "stdafx.h"
#include "ISSModule.h"


ISSModule::ISSModule()
{
}


ISSModule::~ISSModule()
{
}

void ISSModule::Init( ISSModuleName moduleName )
{
	m_ModuleName = moduleName;

	// 자신의 위치 초기화
	GetTransform()->SetPosition( ISS_MODULE_POSITION[static_cast<int>( moduleName )] );

	// 충돌 박스 초기화
	m_CollisionBox.SetCenterPosition( ISS_MODULE_POSITION[static_cast<int>( moduleName )] );
	m_CollisionBox.SetLength( ISS_MODULE_AXIS_LENGTH[static_cast<int>( moduleName )] );
	m_CollisionBox.InitAxisDir();
	m_CollisionBox.InitPointList();
	m_CollisionBox.InitRadius();

	m_ISSPos = 0.0f;
	m_HealthPoint = 1.0f;
}

TeamColor ISSModule::Occupy( TeamColor callerColor )
{
	// 점령 로직이 복잡해지면 오토마타로 변경해서 구현해야?
	if ( m_CurrentOwner == callerColor )
		return m_CurrentOwner;

	m_CurrentOwner = ( m_CurrentOwner == TeamColor::NO_TEAM ) ? callerColor : TeamColor::NO_TEAM;

	printf_s( "[DEBUG] ISS MODULE %d is occupied : %d\n", m_ModuleName, m_CurrentOwner );
	
	return m_CurrentOwner;
}

float ISSModule::DecreaseHP()
{
	// 체력을 일정 수치 깎는다.
	m_HealthPoint -= ISS_BASE_DAMAGE;

	if ( m_HealthPoint < 0 )
		m_HealthPoint = 0.0f;

	printf_s( "[DEBUG] ISS MODULE %d HP : %f\n", m_ModuleName, m_HealthPoint );

	return m_HealthPoint;
}

const CollisionBox* ISSModule::GetControlPointBox()
{
	// m_ControlPoint의 충돌 박스를 계산해서 반환
	// return m_ControlPoint.GetCollisionBox();

	// 우선은 모듈 자체의 충돌 박스 반환
	return GetCollisionBox();
}

void ISSModule::UpdateItSelf( float dTime )
{
	// ISS의 위치를 반영해서 자신의 위치를 수정한다.
	// m_Matrix를 수정해야 하는데 _43 성분이 현재 z 위치
	m_Matrix._43 = m_ISSPos;
}