#pragma once

#include "GameConfig.h"

struct ST_OBB
{
	D3DXMATRIXA16*				m_Transform;	// 원본 오브젝트의 현재 회전 행렬
	D3DXVECTOR3					m_CenterPos;	// 기준점 - 상자 중심
	std::array<D3DXVECTOR3, 3>	m_AxisDir;		// 월드 좌표계를 기준으로 상자 좌표계의 세 축 (박스의 회전 상태)
	std::array<float, 3>		m_AxisLen;		// 각각의 축에 대한 길이 (박스 크기)
	std::array<D3DXVECTOR3, 8>	m_PointList;	// 각 지점 좌표들을 아예 계산하지 말고 박아두자
};