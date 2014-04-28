/*
	Actor를 상속받은 캐릭터
	움직임과 각종 스킬들의 인터페이스를 구현한다.
	세부 클래스는 하위 클래스에서 구현할 것
	2014. 4. 21 최경욱
*/

#pragma once

#include "BaseObject.h"
#include "rigidbody.h"
#include "ClassComponent.h"

class Actor : public BaseObject
{
public:
	Actor();
	virtual ~Actor();

	void GoForward() { m_CharacterClass->GoForward( GetViewDirection(), m_RigidBody ); }	
	void Stop() { m_CharacterClass->Stop( m_RigidBody ); }
	void TurnBody( float x, float y, float z ) { m_CharacterClass->TurnBody( m_Rotation, x, y, z ); }

	void SetAccelerarion( const D3DXVECTOR3 &direction );

	void IncreaseVelocity( const D3DXVECTOR3 &deltaVelocity );

	D3DXVECTOR3 GetVelocity() const { return m_RigidBody.m_Velocity; }

	float GetMass() const { return m_RigidBody.m_Mass; }
	

protected:
	std::shared_ptr<ClassComponent> m_CharacterClass;
	Rigidbody	m_RigidBody;

	bool		m_IsAccelerating = false;
	DWORD		m_AccelerationStart = 0;

private:
	virtual void UpdateItSelf( float dTime ) { UNREFERENCED_PARAMETER( dTime ); }
};

