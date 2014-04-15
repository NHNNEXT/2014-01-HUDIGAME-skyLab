#pragma once
#include "DDObject.h"

class DDCamera;
class Character;

class Player :
	public DDObject
{
public:
	Player();
	Player( int playerId );
	virtual ~Player();

	static Player* Create( int playerId );
	void Init();	

	// �ۼ��� : �ְ��
	// ���� �ٶ󺸴� �������� ���ӵ� �ο�
	// �Լ� �̸� �ٲ�� �� �� ���� GoForward ���� �ɷ�
	// SetAcceleration�� m_Acc�� get, set�� �� ����ؾ��ҵ�
	void SetAcceleration();
	
	// ���ӵ� �� �ӵ� 0���� ����
	void Stop();

	// �ٶ󺸴� ���� ȸ��
	void RotateDicrection(double x, double y);

	DDVECTOR3 GetVelocity() const { return m_Velocity; }
	void SetVelocity( DDVECTOR3 val ) { m_Velocity = val; }
	
	// �ӽ÷� �̸��� SetAccel, GetAccel������ �� ���Ŀ� SetAcceleration�� �Բ� ���� ��
	// 4.15 �輺ȯ
	DDVECTOR3 GetAccel() const { return m_Acceleration; }
	void SetAccel( DDVECTOR3 val ) { m_Acceleration = val; }


	int GetPlayerId() const { return m_PlayerId; }
	void SetPlayerId( int val ) { m_PlayerId = val; }

private:
	virtual void UpdateItSelf( float dTime );

	int			m_PlayerId = -1;
	DDCamera*	m_Camera;
	Character*	m_Character;
	DDVECTOR3	m_Acceleration; // �ڵ����� 0, 0, 0���� �ʱ�ȭ �ǳ�?
	DDVECTOR3	m_Velocity;
	bool		m_IsAccelerating = 0;
	DWORD		m_AccelerationStart = 0;
};

