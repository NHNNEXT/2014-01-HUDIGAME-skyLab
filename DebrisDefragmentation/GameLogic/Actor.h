/*
	Actor를 상속받은 캐릭터
	움직임과 각종 스킬들의 인터페이스를 구현한다.
	세부 클래스는 하위 클래스에서 구현할 것
	2014. 4. 21 최경욱
*/

#pragma once

#include "ServerObject.h"
#include "rigidbody.h"
#include "Avatar.h"

class Actor : public ServerObject
{
public:
	Actor();
	virtual ~Actor();

	void SetAcceleration();
	void Stop();

	D3DXVECTOR3 GetVelocity() { return m_RigidBody.velocity; }
	

protected:
	RIGIDBODY	m_RigidBody;
	Avatar*		m_Avatar;

	bool		m_IsAccelerating = false;
	DWORD		m_AccelerationStart = 0;

private:
	virtual void UpdateItSelf( float dTime ) { UNREFERENCED_PARAMETER( dTime ); }
};

