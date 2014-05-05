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

	void	InitTeamPosition();
	ClassComponent& GetClassComponent() { return *m_CharacterClass.get(); }
	void	GoForward() { m_CharacterClass->GoForward( GetViewDirection(), m_RigidBody ); }	
	void	Stop() { m_CharacterClass->Stop( m_RigidBody ); }	
	void	TurnBody( float x, float y, float z ) { m_CharacterClass->TurnBody( m_Rotation, x, y, z ); }

	void	SetAccelerarion( const D3DXVECTOR3 &direction );
	void	IncreaseVelocity( const D3DXVECTOR3 &deltaVelocity );

	D3DXVECTOR3 GetVelocity() const { return m_RigidBody.m_Velocity; }

	// 지정한 축과 각속도로 자전
	// input : 자전축은 물체의 로컬좌표계 기준으로 사용, 각속도는 말그대로 단위 시간에 회전하는 각도
	void SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity );

	// 현재 자전에 추가 자전 요소 추가 : 차차 구현
	void AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity );

	// 자전 금지
	void StopSpin();

	float	GetMass() const { return m_RigidBody.m_Mass; }
	bool	IsMoving() const { return m_MovingFlag; }
	void	SetMovingFlag( bool flag ) { m_MovingFlag = flag; }

protected:
	std::shared_ptr<ClassComponent> m_CharacterClass;
	Rigidbody	m_RigidBody;
	bool		m_MovingFlag = true;

private:
	virtual void UpdateItSelf( float dTime ) { UNREFERENCED_PARAMETER( dTime ); }
};

