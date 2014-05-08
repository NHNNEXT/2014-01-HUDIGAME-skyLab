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


	///# 아래 코드 간단하게 될 것 같은데.. ISSModuleName::PARTxxx와 ISS_MODULE_POSITION[xxx] 1:1 맵핑 안되나?
	// 어떤 모듈이 되는지에 따라서 위치 정보 바꿔가면서 초기화
	switch ( m_ModuleName )
	{
	case ISSModuleName::NO_MODULE:
		// 여기 들어오면 안 된다. ///# 그러면 assert걸어라..
		break;
	case ISSModuleName::PART0:
		SetPosition( ISS_MODULE_POSITION[0] );

		m_CollisionBox.SetCenterPosition( ISS_MODULE_POSITION[0] );
		m_CollisionBox.SetLength( ISS_MODULE_AXIS_LENGTH[0] );
		m_CollisionBox.InitAxisDir();
		m_CollisionBox.InitPointList();
		m_CollisionBox.InitRadius();

		// m_ControlPoint의 collisionBox도 초기화
		// m_ControlPoint.SetPosition( 0.0f, 0.0f, 0.0f );
		break;
	case ISSModuleName::PART1:
		SetPosition( ISS_MODULE_POSITION[1] );

		m_CollisionBox.SetCenterPosition( ISS_MODULE_POSITION[1] );
		m_CollisionBox.SetLength( ISS_MODULE_AXIS_LENGTH[1] );
		m_CollisionBox.InitAxisDir();
		m_CollisionBox.InitPointList();
		m_CollisionBox.InitRadius();

		// m_ControlPoint의 collisionBox도 초기화
		// m_ControlPoint.SetPosition( 0.0f, 0.0f, 0.0f );
		break;
	case ISSModuleName::PART2:
		SetPosition( ISS_MODULE_POSITION[2] );

		m_CollisionBox.SetCenterPosition( ISS_MODULE_POSITION[2] );
		m_CollisionBox.SetLength( ISS_MODULE_AXIS_LENGTH[2] );
		m_CollisionBox.InitAxisDir();
		m_CollisionBox.InitPointList();
		m_CollisionBox.InitRadius();

		// m_ControlPoint의 collisionBox도 초기화
		// m_ControlPoint.SetPosition( 0.0f, 0.0f, 0.0f );
		break;
	case ISSModuleName::PART3:
		SetPosition( ISS_MODULE_POSITION[3] );

		m_CollisionBox.SetCenterPosition( ISS_MODULE_POSITION[3] );
		m_CollisionBox.SetLength( ISS_MODULE_AXIS_LENGTH[3] );
		m_CollisionBox.InitAxisDir();
		m_CollisionBox.InitPointList();
		m_CollisionBox.InitRadius();

		// m_ControlPoint의 collisionBox도 초기화
		// m_ControlPoint.SetPosition( 0.0f, 0.0f, 0.0f );
		break;
	case ISSModuleName::PART4:
		SetPosition( ISS_MODULE_POSITION[4] );

		m_CollisionBox.SetCenterPosition( ISS_MODULE_POSITION[4] );
		m_CollisionBox.SetLength( ISS_MODULE_AXIS_LENGTH[4] );
		m_CollisionBox.InitAxisDir();
		m_CollisionBox.InitPointList();
		m_CollisionBox.InitRadius();

		// m_ControlPoint의 collisionBox도 초기화
		// m_ControlPoint.SetPosition( 0.0f, 0.0f, 0.0f );
		break;
	case ISSModuleName::PART5:
		SetPosition( ISS_MODULE_POSITION[5] );

		m_CollisionBox.SetCenterPosition( ISS_MODULE_POSITION[5] );
		m_CollisionBox.SetLength( ISS_MODULE_AXIS_LENGTH[5] );
		m_CollisionBox.InitAxisDir();
		m_CollisionBox.InitPointList();
		m_CollisionBox.InitRadius();

		// m_ControlPoint의 collisionBox도 초기화
		// m_ControlPoint.SetPosition( 0.0f, 0.0f, 0.0f );
		break;
	case ISSModuleName::PART6:
		SetPosition( ISS_MODULE_POSITION[6] );

		m_CollisionBox.SetCenterPosition( ISS_MODULE_POSITION[6] );
		m_CollisionBox.SetLength( ISS_MODULE_AXIS_LENGTH[6] );
		m_CollisionBox.InitAxisDir();
		m_CollisionBox.InitPointList();
		m_CollisionBox.InitRadius();

		// m_ControlPoint의 collisionBox도 초기화
		// m_ControlPoint.SetPosition( 0.0f, 0.0f, 0.0f );
		break;
	case ISSModuleName::PART7:
		SetPosition( ISS_MODULE_POSITION[7] );

		m_CollisionBox.SetCenterPosition( ISS_MODULE_POSITION[7] );
		m_CollisionBox.SetLength( ISS_MODULE_AXIS_LENGTH[7] );
		m_CollisionBox.InitAxisDir();
		m_CollisionBox.InitPointList();
		m_CollisionBox.InitRadius();

		// m_ControlPoint의 collisionBox도 초기화
		// m_ControlPoint.SetPosition( 0.0f, 0.0f, 0.0f );
		break;
	case ISSModuleName::PART8:
		SetPosition( ISS_MODULE_POSITION[8] );

		m_CollisionBox.SetCenterPosition( ISS_MODULE_POSITION[8] );
		m_CollisionBox.SetLength( ISS_MODULE_AXIS_LENGTH[8] );
		m_CollisionBox.InitAxisDir();
		m_CollisionBox.InitPointList();
		m_CollisionBox.InitRadius();

		// m_ControlPoint의 collisionBox도 초기화
		// m_ControlPoint.SetPosition( 0.0f, 0.0f, 0.0f );
		break;
	case ISSModuleName::PART9:
		SetPosition( ISS_MODULE_POSITION[9] );

		m_CollisionBox.SetCenterPosition( ISS_MODULE_POSITION[9] );
		m_CollisionBox.SetLength( ISS_MODULE_AXIS_LENGTH[9] );
		m_CollisionBox.InitAxisDir();
		m_CollisionBox.InitPointList();
		m_CollisionBox.InitRadius();

		// m_ControlPoint의 collisionBox도 초기화
		// m_ControlPoint.SetPosition( 0.0f, 0.0f, 0.0f );
		break;
	default:
		break;
	}
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