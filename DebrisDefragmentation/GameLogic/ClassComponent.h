#pragma once
#include "GameOption.h"
#include "GameMacro.h"
#include "Transform.h"
#include "Rigidbody.h"

class ClassComponent
{
public:
	ClassComponent();
	virtual ~ClassComponent();

	CREATE_FUNC( ClassComponent ); ///# 클래스 콤포넌트가 직접 생성되는 경우가 의도 맞나? 잘못된 디자인 같은데...

	// 작성자 : 최경욱	
	// 
	void GoForward( D3DXVECTOR3 viewDirection ); // 현재 바라보는 방향으로 가속도 부여
	void Stop();	// 가속도 및 속도 0으로 변경	

	// 바라보는 방향으로 몸을 회전 turn body to viewing direction 04.27김성환
	void	TurnBody( Transform& tr, float x, float y, float z ) { tr.SetRotation(x,y,z); }

	void	AddForce( const D3DXVECTOR3 &direction );

	DWORD	GetAccelerationStartTime() const { return m_AccelerationStartTime; }
	void	SetAccelerationStartTime( DWORD val ) { m_AccelerationStartTime = val; }

	bool	IsAccelerating() const { return m_IsAccelerating; }
	void	SetIsAccelerating( bool val ) { m_IsAccelerating = val; }

	void SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity );

	// 현재 자전에 추가 자전 요소 추가 : 차차 구현
	void AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity );

	// 자전 금지
	void StopSpin();

	void	SetSpinnigFlag( bool flag ) { m_IsSpin = flag; }
	bool	IsSpinning() { return m_IsSpin; }
	void	AddSpinTime( float dt ) { m_SpinTime += dt; }
	float	GetSpinTime() { return m_SpinTime; }
	void	SetSpinTime( float time ) { m_SpinTime = time; }
	
	int		GetFuel() const { return m_Fuel; }
	void	SetFuel( int val ) { m_Fuel = val; }

	int		GetOxygen() const { return m_Oxygen; }
	void	SetOxygen( int val ) { m_Oxygen = val; }
	void	IncreaseOxygen( int val ) { m_Oxygen += val; }

	int		GetHP() const { return m_HP; }
	void	SetHP( int val ) { m_HP = val; }

	bool	IsAlive() { return ( m_HP > 0 ) ? true : false; }
	bool	UseFuel( int fuelUse );
	bool	UseOxygen(int oxygenUse);

	Rigidbody	GetRigidbody() { return m_Rigidbody; }
	void		SetRigidbody( Rigidbody val ) { m_Rigidbody = val; }

	float&			GetMass() { return m_Rigidbody.m_Mass; }
	D3DXVECTOR3&	GetAcceleration() { return m_Rigidbody.m_Acceleration; }
	D3DXVECTOR3&	GetVelocity() { return m_Rigidbody.m_Velocity; }
	D3DXVECTOR3&	GetSpinAxis() { return m_Rigidbody.m_SpinAxis; }
	float			GetSpinAngle() { return m_Rigidbody.m_SpinAngle; }
	void		SetMass( float mass ) { m_Rigidbody.m_Mass = mass; }
	void		SetAcceleration( D3DXVECTOR3 accel ) { m_Rigidbody.m_Acceleration = accel; }
	void		SetVelocity( D3DXVECTOR3 velocity ) { m_Rigidbody.m_Velocity = velocity; }
	void		SetSpinAxis( D3DXVECTOR3 spinAxis ) { m_Rigidbody.m_SpinAxis = spinAxis; }
	void		SetSpinAngle( float spinAngle ) { m_Rigidbody.m_SpinAngle = spinAngle; }


	TeamColor	GetTeam() const { return m_Team; }
	void		SetTeam( TeamColor val ) { m_Team = val; }

protected:	
	bool		m_IsAccelerating = false;
	bool		m_IsSpin = false;	
	
	TeamColor	m_Team = TeamColor::NO_TEAM;
	Rigidbody	m_Rigidbody;
	
	// 산소 및 추진체 관련
	int			m_Oxygen = DEFAULT_OXYGEN;
	int			m_Fuel = DEFAULT_FUEL;
	int			m_HP = DEFAULT_HP;
	DWORD		m_AccelerationStartTime = 0;
	float		m_SpinTime = 0.0f;
};

