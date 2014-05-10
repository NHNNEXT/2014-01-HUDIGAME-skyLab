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
	SetPosition( ISS_MODULE_POSITION[static_cast<int>( moduleName )] );

	// 충돌 박스 초기화
	m_CollisionBox.SetCenterPosition( ISS_MODULE_POSITION[static_cast<int>( moduleName )] );
	m_CollisionBox.SetLength( ISS_MODULE_AXIS_LENGTH[static_cast<int>( moduleName )] );
	m_CollisionBox.InitAxisDir();
	m_CollisionBox.InitPointList();
	m_CollisionBox.InitRadius();
}

TeamColor ISSModule::Occupy( TeamColor callerColor )
{
	// 점령 로직이 복잡해지면 오토마타로 변경해서 구현해야?
	if ( m_CurrentOwner == callerColor )
		return m_CurrentOwner;

	m_CurrentOwner = ( m_CurrentOwner == TeamColor::NO_TEAM ) ? callerColor : TeamColor::NO_TEAM;

	printf_s( "[DEBUG] ISS MODULE %d is occupied : %d", m_ModuleName, m_CurrentOwner );
	
	return m_CurrentOwner;
}

float ISSModule::DecreaseHP()
{
	// 체력을 일정 수치 깎는다.
	m_HealthPoint -= ISS_BASE_DAMAGE;

	if ( m_HealthPoint < 0 )
		m_HealthPoint = 0.0f;

	printf_s( "[DEBUG] ISS MODULE %d HP : %f", m_ModuleName, m_HealthPoint );

	return m_HealthPoint;
}

const CollisionBox* ISSModule::GetControlPointBox()
{
	// m_ControlPoint의 충돌 박스를 계산해서 반환
	// return m_ControlPoint.GetCollisionBox();

	// 우선은 모듈 자체의 충돌 박스 반환
	return GetCollisionBox();
}