#include "stdafx.h"
#include "ISSModule.h"
#include "GameData.h"


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
	//GetTransform()->SetPosition( ISS_MODULE_POSITION[static_cast<int>( moduleName )] );
	GetTransform()->SetPosition( g_GameData->GetISSPosition( moduleName ) );
	// 충돌 박스 초기화
	//m_CollisionBox.SetCenterPosition( ISS_MODULE_POSITION[static_cast<int>( moduleName )] );
	m_CollisionBox.SetCenterPosition( g_GameData->GetISSPosition( moduleName ) );
	//m_CollisionBox.SetLength( ISS_MODULE_AXIS_LENGTH[static_cast<int>( moduleName )] );
	m_CollisionBox.SetLength( g_GameData->GetISSModuleAxisLength( moduleName ) );
	m_CollisionBox.InitAxisDir();
	m_CollisionBox.InitPointList();
	m_CollisionBox.InitRadius();

	//m_ControlBox.SetCenterPosition( ISS_MODULE_POSITION[static_cast<int>( moduleName )] );
	m_ControlBox.SetCenterPosition( g_GameData->GetISSPosition( moduleName ) );
	//m_ControlBox.SetLength( CONTROL_POINT_AXIS_LENGTH );
	m_ControlBox.SetLength( CONTROL_POINT_AXIS_LENGTH );
	m_ControlBox.InitAxisDir();
	m_ControlBox.InitPointList();
	m_ControlBox.InitRadius();

	m_ISSPos = 0.0f;
	m_HealthPoint = 1.0f;
	m_CurrentOwner = TeamColor::NO_TEAM;
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

void ISSModule::DecreaseHP()
{
	// 체력을 일정 수치 깎는다.
	m_HealthPoint -= ISS_BASE_DAMAGE;

	if ( m_HealthPoint < 0 )
		m_HealthPoint = 0.0f;

	printf_s( "[DEBUG] ISS MODULE %d HP : %f\n", m_ModuleName, m_HealthPoint );
}

const CollisionBox* ISSModule::GetControlPointBox()
{
	// GetCollisionBox()와 같은 방식으로 m_ControlBox에 m_Matrix의 변환을 적용해서 그 결과를 반환한다.
	// 이 함수를 호출하는 것은 ISS 클래스이고, 
	D3DXVECTOR4 tempMat;

	// 현재 위치
	D3DXVec3Transform( &tempMat, &m_ControlBox.m_CenterPos, &m_Matrix );
	m_TransformedBoxCache.m_CenterPos = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

	// 각 점 좌표
	D3DXVec3TransformCoordArray(
		m_TransformedBoxCache.m_PointList.data(), sizeof( D3DXVECTOR3 ),
		m_ControlBox.m_PointList.data(), sizeof( D3DXVECTOR3 ),
		&m_Matrix, BOX_POINT_COUNT
		);

	// 축
	for ( int i = 0; i < 3; ++i )
	{
		// 마지막 항을 0으로 해야 평행이동 값이 벡터에 반영되지 않음
		D3DXVECTOR4 tempAxis = D3DXVECTOR4( m_ControlBox.m_AxisDir[i].x, m_ControlBox.m_AxisDir[i].y, m_ControlBox.m_AxisDir[i].z, 0 );

		D3DXVec4Transform( &tempMat, &tempAxis, &m_Matrix );
		m_TransformedBoxCache.m_AxisDir[i] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

		m_TransformedBoxCache.m_AxisLen[i] = m_ControlBox.m_AxisLen[i];
	}

	m_TransformedBoxCache.m_Radius = m_ControlBox.m_Radius;

	return &m_TransformedBoxCache;
}

void ISSModule::UpdateItSelf( float dTime )
{
	// ISS의 위치를 반영해서 자신의 위치를 수정한다.
	// m_Matrix를 수정해야 하는데 _43 성분이 현재 z 위치
	m_Matrix._43 = m_ISSPos;
}