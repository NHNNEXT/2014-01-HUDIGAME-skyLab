#pragma once

/*
	�ۼ��� : �ְ��
	�ۼ��� : 2014. 4. 6
	���� : ������ ��� ����(��ü �, ȸ��, �浹 ��)
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
		input : ���� ��ġ, �ӵ�, �ð� ��ȭ��
		output : ������Ʈ�� ���� ��ġ
		���� : ��ӿ�� ��� ���, ���ӵ��� ���� ����� �ʿ��ϸ� �����ε��� �Լ� ����� ��
	*/
	void CalcCurrentPosition( _Inout_ DDVector3* pos, const DDVector3 &velocity, float dt );

	/*
		input : ���� ��ġ, ���� �ӵ�, ���ӵ�, �ð� ��ȭ��
		output : ������Ʈ�� ���� ��ġ, ������Ʈ�� ���� �ӵ�
		���� : ���ӵ��� ���� ��� ��� ���, ��ӿ�� ��� �����ε��� �Լ� ����� ��
	*/
	void CalcCurrentPosition( _Inout_ DDVector3* pos, _Inout_ DDVector3* velocity, const DDVector3 &acceleration, float dt );
};

