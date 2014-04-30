#pragma once

#include "GameConfig.h"

struct CollisionBox
{
	CollisionBox()
	{
		for ( unsigned int i = 0; i < VECTOR_DIRECTION_3; ++i )
		{
			m_AxisDir[i] = ZERO_VECTOR3;
			m_AxisLen[i] = 0.0f;
		}

		for ( unsigned int i = 0; i < BOX_POINT_COUNT; ++i )
		{
			m_PointList[i] = ZERO_VECTOR3;
		}
	}

	///# 헐? 위험한 코드.. 이렇게 큰 객체를 그냥 복사 대입? 그리고 멤버중에 포인터도 있는데??
	///# 포인터 복사는 정말 위험하다.. 
	CollisionBox& operator=( const CollisionBox& rhs )
	{
		m_Transform = rhs.m_Transform;
		m_CenterPos = rhs.m_CenterPos;
		m_AxisDir = rhs.m_AxisDir;
		m_AxisLen = rhs.m_AxisLen;
		m_PointList = rhs.m_PointList;
		m_Radius = rhs.m_Radius;

		return *this;
	}

	D3DXMATRIXA16*								m_Transform = nullptr;				// 원본 오브젝트의 현재 회전 행렬
	D3DXVECTOR3									m_CenterPos{ 0.0f, 0.0f, 0.0f };	// 기준점 - 상자 중심
	std::array<D3DXVECTOR3, VECTOR_DIRECTION_3>	m_AxisDir;							// 월드 좌표계를 기준으로 상자 좌표계의 세 축 (박스의 회전 상태)
	std::array<float, VECTOR_DIRECTION_3>		m_AxisLen;							// 각각의 축에 대한 길이 (박스 크기)
	std::array<D3DXVECTOR3, BOX_POINT_COUNT>	m_PointList;						// 각 지점 좌표들을 아예 계산하지 말고 박아두자
	float										m_Radius = 0.0f;					// 충돌 체크를 할 조건 설정 (너무 멀면 안 하려고)
};