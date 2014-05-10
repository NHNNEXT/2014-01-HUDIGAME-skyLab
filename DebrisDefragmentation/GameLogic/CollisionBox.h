#pragma once

#include "GameOption.h"

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

	void SetCenterPosition( const D3DXVECTOR3 &newCenterPos )
	{
		m_CenterPos = newCenterPos;
	}

	void SetLength( const D3DXVECTOR3 &length )
	{
		m_AxisLen = D3DXVECTOR3( length );
	}

	// Init함수는 순서에 유의할 것
	void InitAxisDir()
	{
		m_AxisDir[0] = X_AXIS_VECTOR3;
		m_AxisDir[1] = Y_AXIS_VECTOR3;
		m_AxisDir[2] = Z_AXIS_VECTOR3;
	}

	void InitPointList()
	{
		m_PointList[0] = D3DXVECTOR3(
			m_CenterPos.x - m_AxisLen.x,
			m_CenterPos.y + m_AxisLen.y,
			m_CenterPos.z + m_AxisLen.z
			);
		m_PointList[1] = D3DXVECTOR3(
			m_CenterPos.x + m_AxisLen.x,
			m_CenterPos.y + m_AxisLen.y,
			m_CenterPos.z + m_AxisLen.z
			);
		m_PointList[2] = D3DXVECTOR3(
			m_CenterPos.x + m_AxisLen.x,
			m_CenterPos.y + m_AxisLen.y,
			m_CenterPos.z - m_AxisLen.z
			);
		m_PointList[3] = D3DXVECTOR3(
			m_CenterPos.x - m_AxisLen.x,
			m_CenterPos.y + m_AxisLen.y,
			m_CenterPos.z - m_AxisLen.z
			);
		m_PointList[4] = D3DXVECTOR3(
			m_CenterPos.x - m_AxisLen.x,
			m_CenterPos.y - m_AxisLen.y,
			m_CenterPos.z + m_AxisLen.z
			);
		m_PointList[5] = D3DXVECTOR3(
			m_CenterPos.x + m_AxisLen.x,
			m_CenterPos.y - m_AxisLen.y,
			m_CenterPos.z + m_AxisLen.z
			);
		m_PointList[6] = D3DXVECTOR3(
			m_CenterPos.x + m_AxisLen.x,
			m_CenterPos.y - m_AxisLen.y,
			m_CenterPos.z - m_AxisLen.z
			);
		m_PointList[7] = D3DXVECTOR3(
			m_CenterPos.x - m_AxisLen.x,
			m_CenterPos.y - m_AxisLen.y,
			m_CenterPos.z - m_AxisLen.z
			);
	}

	void InitRadius()
	{
		m_Radius = sqrt( m_AxisLen.x * m_AxisLen.x
			+ m_AxisLen.y * m_AxisLen.y
			+ m_AxisLen.z * m_AxisLen.z );
	}

	D3DXVECTOR3									m_CenterPos{ 0.0f, 0.0f, 0.0f };	// 기준점 - 상자 중심
	std::array<D3DXVECTOR3, VECTOR_DIRECTION_3>	m_AxisDir;							// 월드 좌표계를 기준으로 상자 좌표계의 세 축 (박스의 회전 상태)
	D3DXVECTOR3									m_AxisLen;							// 각각의 축에 대한 길이 (박스 크기)
	std::array<D3DXVECTOR3, BOX_POINT_COUNT>	m_PointList;						// 각 지점 좌표들을 아예 계산하지 말고 박아두자
	float										m_Radius = 0.0f;					// 충돌 체크를 할 조건 설정 (너무 멀면 안 하려고)
};