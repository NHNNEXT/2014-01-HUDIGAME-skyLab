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
	// 어떤 모듈이 되는지에 따라서 위치 정보 바꿔가면서 초기화
	switch ( moduleName )
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

void DecreaseHP()
{
	// 체력을 일정 수치 깎는다.
}