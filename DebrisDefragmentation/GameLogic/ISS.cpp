#include "stdafx.h"
#include "ISS.h"


ISS::ISS()
{
}


ISS::~ISS()
{
}

void ISS::Init()
{
	// 각각의 모듈을 초기화

}

void ISS::UpdateItSelf( float dTime )
{
	// 점령 상태 확인
	// 점령 상태에 따라서 현재 위치 이동
	// 자신의 위치에 따라서 m_Matrix 업데이트
}

ISSModuleName ISS::Occupy( int skillUserId )
{
	// skillUserId를 이용해서 스킬을 사용한 유저의 정보를 이용해서
	// 자신에게 등록된 모듈들을 차례대로 돌면서 
	// 유저의 position 에서 viewDirection 방향의 ray를 쏴서 걸리는 점령 포인트가 있는지 확인 - 거리도 포함해서 계산
	// 걸리는 애가 있으면 그 모듈의 상태를 바꾸고 변화가 적용된 모듈 id를 반환
}

std::tuple<ISSModuleName, float> ISS::Destroy( int skillUserId )
{
	// skillUserId를 이용해서 스킬을 사용한 유저의 정보를 이용해서
	// 자신에게 등록된 모듈들을 차례대로 돌면서 
	// 유저의 position 에서 viewDirection 방향의 ray를 쏴서 걸리는 모듈이 있는지 확인 - 거리도 포함해서 계산
	// 걸리는 애가 있으면 체력을 낮추고 걸린 모듈의 id와 변경된 체력을 tuple에 담아서 리턴
}