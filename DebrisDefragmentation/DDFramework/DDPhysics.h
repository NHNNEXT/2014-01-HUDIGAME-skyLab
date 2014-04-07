#pragma once

/*
	�ۼ��� : �ְ��
	�ۼ��� : 2014. 4. 6
	���� : ������ ��� ����(��ü �, ȸ��, �浹 ��)
*/

#include "DDConfig.h"
#include "DDPoint.h"

class DDPhysics
{
public:
	DDPhysics();
	~DDPhysics();

	/*
		input : ���� ��ġ, �ӵ�, �ð� ��ȭ��
		output : ������Ʈ�� ���� ��ġ
		���� : ��ӿ�� ��� ���, ���ӵ��� ���� ����� �ʿ��ϸ� �����ε��� �Լ� ����� ��
	*/
	void CalcCurrentPosition( _Inout_ DDVECTOR3* pos, const DDVECTOR3 &velocity, float dt );

	/*
		input : ���� ��ġ, ���� �ӵ�, ���ӵ�, �ð� ��ȭ��
		output : ������Ʈ�� ���� ��ġ, ������Ʈ�� ���� �ӵ�
		���� : ���ӵ��� ���� ��� ��� ���, ��ӿ�� ��� �����ε��� �Լ� ����� ��
	*/
	void CalcCurrentPosition( _Inout_ DDVECTOR3* pos, _Inout_ DDVECTOR3* velocity, const DDVECTOR3 &acceleration, float dt );
};

