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

	// 어떤 모듈이 되는지에 따라서 위치 정보 바꿔가면서 초기화
	switch ( m_ModuleName )
	{
	case ISSModuleName::NO_MODULE:
		break;
	case ISSModuleName::PART1:
		break;
	case ISSModuleName::PART2:
		break;
	case ISSModuleName::PART3:
		break;
	case ISSModuleName::PART4:
		break;
	case ISSModuleName::PART5:
		break;
	case ISSModuleName::PART6:
		break;
	case ISSModuleName::PART7:
		break;
	case ISSModuleName::PART8:
		break;
	default:
		break;
	}
}

TeamColor ISSModule::Occupy( TeamColor callerColor )
{
	// 점령 로직이 복잡해지면 오토마타로 변경해서 구현해야?
	m_CurrentOwner = ( m_CurrentOwner == TeamColor::NO_TEAM ) ? callerColor : TeamColor::NO_TEAM;
	
	return m_CurrentOwner;
}

float ISSModule::DecreaseHP()
{
	// 체력을 일정 수치 깎는다.
	return m_HealthPoint;
}

const CollisionBox* ISSModule::GetControlPointBox()
{
	// m_ControlPoint의 충돌 박스를 계산해서 반환
	return m_ControlPoint.GetCollisionBox();
}