/*
	Actor를 상속받은 캐릭터
	움직임과 각종 스킬들의 인터페이스를 구현한다.
	세부 클래스는 하위 클래스에서 구현할 것
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

	/*	물체 이동 회전	*/
	// 인자로 넘긴 방향으로 가속
	void	Move( const D3DXVECTOR3& direction );
	void	Stop();

	DWORD	GetAccelerationStartTime() const { return m_AccelerationStartTime; }
	void	SetAccelerationStartTime( DWORD val ) { m_AccelerationStartTime = val; }

	void	IncreaseVelocity( const D3DXVECTOR3 &deltaVelocity );

	// 기존의 setAcceleration. 이름이 acceleration 값을 set하는 함수랑 같아서 변경함.
	void	AddForce( const D3DXVECTOR3 &direction );

	bool	IsMoving() const { return m_MovingFlag; }
	void	SetMovingFlag( bool flag ) { m_MovingFlag = flag; }

	Rigidbody*	GetRigidbody() { return &m_Rigidbody; }

	bool	IsAccelerating() const { return m_Rigidbody.m_IsAccelerating; }
	void	SetIsAccelerating( bool val ) { m_Rigidbody.m_IsAccelerating = val; }

	const float&		GetMass() const { return m_Rigidbody.m_Mass; }
	const D3DXVECTOR3&	GetAcceleration() const { return m_Rigidbody.m_Acceleration; }
	const D3DXVECTOR3&	GetVelocity() const { return m_Rigidbody.m_Velocity * m_SpeedConstant; } // 순간 가속을 할 수 있으므로 상수를 곱해서 반환 - 내부에서 직접 참조하면 안 되는데
	const D3DXVECTOR3&	GetSpinAxis() const { return m_Rigidbody.m_SpinAxis; }
	const float&		GetSpinAngle() const { return m_Rigidbody.m_SpinAngle; }

	void	SetMass( float mass ) { m_Rigidbody.m_Mass = mass; }
	void	SetAcceleration( D3DXVECTOR3 accel ) { m_Rigidbody.m_Acceleration = accel; }
	void	SetVelocity( D3DXVECTOR3 velocity ) { m_Rigidbody.m_Velocity = velocity; }
	void	SetSpinAxis( D3DXVECTOR3 spinAxis ) { m_Rigidbody.m_SpinAxis = spinAxis; }
	void	SetSpinAngle( float spinAngle ) { m_Rigidbody.m_SpinAngle = spinAngle; }

	void	SetSpinnigFlag( bool flag ) { m_Rigidbody.m_IsSpin = flag; }
	bool	IsSpinning() { return m_Rigidbody.m_IsSpin; }
	void	AddSpinTime( float dt ) { m_SpinTime += dt; }
	float	GetSpinTime() { return m_SpinTime; }
	void	SetSpinTime( float time ) { m_SpinTime = time; }

	void	SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity );
	void	AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity );
	void	StopSpin();

	void	SetSpeedConstant( float newConstant ) { m_SpeedConstant = newConstant; }
	float	GetSpeedConstant() { return m_SpeedConstant; }

protected:
	Rigidbody	m_Rigidbody;

	DWORD		m_AccelerationStartTime = 0;
	float		m_SpinTime = 0.0f;
	bool		m_MovingFlag = true;
	float		m_SpeedConstant = 1.0f;

private:
	virtual void UpdateItSelf( float dTime );
};

