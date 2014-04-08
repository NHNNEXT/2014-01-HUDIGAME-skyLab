#pragma once
#include "DDObject.h"
#include "DDCamera.h"
#include "Character.h"

class Player :
	public DDObject
{
public:
	Player();
	virtual ~Player();

	CREATE_FUNC( Player );
	void Init();
	
	void Update( float dTime );
	void UpdateItSelf( float dTime );

	// �ۼ��� : �ְ��
	// ���� �ٶ󺸴� �������� ���ӵ� �ο�
	void SetAcceleration();
	
	// ���ӵ� �� �ӵ� 0���� ����
	void Stop();

	// �ٶ󺸴� ���� ȸ��
	void RotateDicrection(float y, float x);

private:
	DDCamera*	m_Camera;
	Character*	m_Character;
	DDVECTOR3	m_Acceleration; // �ڵ����� 0, 0, 0���� �ʱ�ȭ �ǳ�?
	DDVECTOR3	m_Velocity;

	bool		m_IsAccelerating;
	DWORD		m_AccelerationStart;
};

