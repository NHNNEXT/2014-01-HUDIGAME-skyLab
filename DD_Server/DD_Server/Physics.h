#pragma once

#include "GameConfig.h"

/*
�ۼ��� : �ְ��
�ۼ��� : 2014. 4. 6
���� : ������ ��� ����(��ü �, ȸ��, �浹 ��)

�ϴ� ���� �� ���� ����� ������ �����ؼ� ���ϴ� ��
*/

class Physics
{
public:
	Physics();
	~Physics();

	/*
	input : ���� ��ġ, �ӵ�, �ð� ��ȭ��
	output : ������Ʈ�� ���� ��ġ
	���� : ��ӿ�� ��� ���, ���ӵ��� ���� ����� �ʿ��ϸ� �����ε��� �Լ� ����� ��
	*/
	static void CalcCurrentPosition( _Inout_ DDVECTOR3* pos, const DDVECTOR3 &velocity, float dt );

	/*
	input : ���� ��ġ, ���� �ӵ�, ���ӵ�, �ð� ��ȭ��
	output : ������Ʈ�� ���� ��ġ, ������Ʈ�� ���� �ӵ�
	���� : ���ӵ��� ���� ��� ��� ���, ��ӿ�� ��� �����ε��� �Լ� ����� ��
	*/
	static void CalcCurrentPosition( _Inout_ DDVECTOR3* pos, _Inout_ DDVECTOR3* velocity, const DDVECTOR3 &acceleration, float dt );

	/*
	input : ���� ���Ϳ� ����� ����� ���� �ּ�
	output : ���� ������ ��� ����
	*/
	static void GetNormalVector( _In_ DDVECTOR3* srcVec, _Out_ DDVECTOR3* normalVec );
};

