#pragma once

#include "GameConfig.h"
#include <array>

struct ST_OBB
{
	D3DXMATRIXA16*				m_Transform;	// ���� ������Ʈ�� ���� ȸ�� ���
	D3DXVECTOR3					m_CenterPos;	// ������ - ���� �߽�
	std::array<D3DXVECTOR3, 3>	m_AxisDir;		// ���� ��ǥ�踦 �������� ���� ��ǥ���� �� �� (�ڽ��� ȸ�� ����)
	std::array<float, 3>		m_AxisLen;		// ������ �࿡ ���� ���� (�ڽ� ũ��)
	std::array<D3DXVECTOR3, 8>	m_PointList;	// �� ���� ��ǥ���� �ƿ� ������� ���� �ھƵ���
};