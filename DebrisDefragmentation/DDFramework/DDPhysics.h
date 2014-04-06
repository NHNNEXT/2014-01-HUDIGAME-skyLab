#pragma once

/*
	작성자 : 최경욱
	작성일 : 2014. 4. 6
	내용 : 물리적 계산 수행(물체 운동, 회전, 충돌 등)
*/

#include "DDConfig.h"
#include "DDPoint.h"
#include "DDVector3.h"

class DDPhysics
{
public:
	DDPhysics();
	~DDPhysics();

	/*
		input : 현재 위치, 속도, 시간 변화량
		output : 업데이트된 현재 위치
		주의 : 등속운동인 경우 사용, 가속도에 의한 계산이 필요하면 오버로딩된 함수 사용할 것
	*/
	void CalcCurrentPosition( _Inout_ DDVector3* pos, const DDVector3 &velocity, float dt );

	/*
		input : 현재 위치, 현재 속도, 가속도, 시간 변화량
		output : 업데이트된 현재 위치, 업데이트된 현재 속도
		주의 : 가속도에 의한 운동인 경우 사용, 등속운동의 경우 오버로딩된 함수 사용할 것
	*/
	void CalcCurrentPosition( _Inout_ DDVector3* pos, _Inout_ DDVector3* velocity, const DDVector3 &acceleration, float dt );
};

