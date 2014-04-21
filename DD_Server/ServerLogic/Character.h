/*
	Actor를 상속받은 캐릭터
	움직임과 각종 스킬들의 인터페이스를 구현한다.
	세부 클래스는 하위 클래스에서 구현할 것
	2014. 4. 21 최경욱
*/

#pragma once

#include "Actor.h"

class Character : public Actor
{
public:
	Character();
	virtual ~Character();

	void SetAcceleration();
	void Stop();

	D3DXVECTOR3 GetPosition() { return m_Position; }
	D3DXVECTOR3 GetScale() { return m_Scale; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetVelocity() { return m_Velocity; }
	D3DXVECTOR3 GetViewDirection();

protected:
	D3DXVECTOR3	m_Acceleration{ 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3	m_Velocity{ 0.0f, 0.0f, 0.0f };

	bool		m_IsAccelerating = false;
	DWORD		m_AccelerationStart = 0;

private:
	virtual void UpdateItSelf( float dTime ) { UNREFERENCED_PARAMETER( dTime ); }
};

