#pragma once

#include "GameConfig.h"

class PlayerCharacter
{
	// �ƹ����� �ӽ� ������ �� ��
	// Ŭ���̾�Ʈ�� ���� �κ��� �ƿ� �и��ؼ� ���������� ������ �� �ֵ��� �ؾ�
	// ������ �� �κ����� ���� �� �־�� �� 
	// ���� �� ������ �ʿ��� ���� ��� �������� �����ϰ�
	// ĳ���͵��� �������� ����ϴ� �κ��� Ŭ�󿡼��� ���ÿ� ���
public:
	PlayerCharacter( int playerId );
	~PlayerCharacter();

	void update( float dTime );

	void SetPosition( float x, float y, float z ) { m_Position = DDVECTOR3( x, y, z ); }
	void SetScale( float scaleX, float scaleY, float scaleZ ) { m_Scale = DDVECTOR3( scaleX, scaleY, scaleZ ); }
	void SetRotation( float rotationX, float rotationY, float rotationZ ) { m_Rotation = DDVECTOR3( rotationX, rotationY, rotationZ ); }

	void SetAcceleration();
	void Stop();
	void RotateDicrection( float y, float x );

	// player ���� ��������
	int GetPlayerId() { return m_PlayerId; }
	DDVECTOR3 GetPosition() { return m_Position; }
	DDVECTOR3 GetScale() { return m_Scale; }
	DDVECTOR3 GetRotation() { return m_Rotation; }
	DDVECTOR3 GetVelocity( ) { return m_Velocity; }

private:
	DDVECTOR3 GetViewDirection();

	int				m_PlayerId = -1;

	DDVECTOR3		m_Position;
	DDVECTOR3		m_Rotation;
	DDVECTOR3		m_Scale;

	DDVECTOR3		m_Acceleration; 
	DDVECTOR3		m_Velocity;

	bool		m_IsAccelerating;
	DWORD		m_AccelerationStart;
};

