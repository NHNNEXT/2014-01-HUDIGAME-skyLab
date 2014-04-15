#pragma once
#include "DDObject.h"

class DDCamera;
class Character;

class Player :
	public DDObject
{
public:
	Player();
	virtual ~Player();

	CREATE_FUNC( Player );
	void Init();	

	// �ۼ��� : �ְ��
	// ���� �ٶ󺸴� �������� ���ӵ� �ο�
	void SetAcceleration();
	
	// ���ӵ� �� �ӵ� 0���� ����
	void Stop();

	// �ٶ󺸴� ���� ȸ��
	void RotateDicrection(double y, double x);

private:
	virtual void UpdateItSelf( float dTime );

	DDCamera*	m_Camera;
	Character*	m_Character;
	DDVECTOR3	m_Acceleration; // �ڵ����� 0, 0, 0���� �ʱ�ȭ �ǳ�?
	DDVECTOR3	m_Velocity;

	bool		m_IsAccelerating;
	DWORD		m_AccelerationStart;
};

