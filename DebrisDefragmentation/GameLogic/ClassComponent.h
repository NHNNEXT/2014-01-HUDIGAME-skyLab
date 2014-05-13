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

	// 사용자들이 사용하는 스킬들!
	bool GoForward( D3DXVECTOR3 viewDirection ); // 현재 바라보는 방향으로 가속도 부여
	void Stop();	// 가속도 및 속도 0으로 변경	

	// 바라보는 방향으로 몸을 회전 turn body to viewing direction 04.27김성환
	void	TurnBody( Transform& tr, float x, float y, float z ) { tr.SetRotation( x, y, z ); }

	void	SkillPush( ClassComponent* targetComponent, D3DXVECTOR3 force );
	void	SkillPull( ClassComponent* targetComponent, D3DXVECTOR3 force );
	void	SkillShareFuel( ClassComponent* targetComponent );
	void	ResetStatus();





	// 작성자 : 최경욱	
	// 
	

	// 기존의 setAcceleration. 이름이 acceleration 값을 set하는 함수랑 같아서 변경함.
	void	AddForce( const D3DXVECTOR3 &direction );

	DWORD	GetAccelerationStartTime() const { return m_AccelerationStartTime; }
	void	SetAccelerationStartTime( DWORD val ) { m_AccelerationStartTime = val; }

	bool	IsAccelerating() const { return m_Rigidbody.m_IsAccelerating; }
	void	SetIsAccelerating( bool val ) { m_Rigidbody.m_IsAccelerating = val; }

	void SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity );

	// 현재 자전에 추가 자전 요소 추가 : 차차 구현
	void AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity );

	// 자전 금지
	void StopSpin();

	void	SetSpinnigFlag( bool flag ) { m_Rigidbody.m_IsSpin = flag; }
	bool	IsSpinning() { return m_Rigidbody.m_IsSpin; }
	void	AddSpinTime( float dt ) { m_SpinTime += dt; }
	float	GetSpinTime() { return m_SpinTime; }
	void	SetSpinTime( float time ) { m_SpinTime = time; }
	
	float	GetFuel() const { return m_Fuel; }
	void	SetFuel( float val ) { m_Fuel = val; }

	float	GetOxygen() const { return m_Oxygen; }
	void	SetOxygen( float val ) { m_Oxygen = val; }
	void	IncreaseOxygen( float val ) { m_Oxygen += val; }
	void	IncreaseFuel( float val ) { m_Fuel += val; }

	float	GetHP() const { return m_HP; }
	void	SetHP( float val ) { m_HP = val; }

	bool	IsAlive() { return ( m_HP > 0.0f ) ? true : false; }
	bool	UseFuel( float fuelUse );
	bool	UseOxygen( float oxygenUse );

	// 주기적으로 처리해야 하는 일들
	// 예를 들어 산소량 감소와 같은 일을 처리 
	void	Update( float dt );

// 	Rigidbody	GetRigidbody() { return m_Rigidbody; }
// 	void		SetRigidbody( Rigidbody val ) { m_Rigidbody = val; }

	const float&		GetMass() const { return m_Rigidbody.m_Mass; }
	const D3DXVECTOR3&	GetAcceleration() const { return m_Rigidbody.m_Acceleration; }
	const D3DXVECTOR3&	GetVelocity() const { return m_Rigidbody.m_Velocity; }
	const D3DXVECTOR3&	GetSpinAxis() const { return m_Rigidbody.m_SpinAxis; }
	const float&		GetSpinAngle() const { return m_Rigidbody.m_SpinAngle; }
	void		SetMass( float mass ) { m_Rigidbody.m_Mass = mass; }
	void		SetAcceleration( D3DXVECTOR3 accel ) { m_Rigidbody.m_Acceleration = accel; }
	void		SetVelocity( D3DXVECTOR3 velocity ) { m_Rigidbody.m_Velocity = velocity; }
	void		SetSpinAxis( D3DXVECTOR3 spinAxis ) { m_Rigidbody.m_SpinAxis = spinAxis; }
	void		SetSpinAngle( float spinAngle ) { m_Rigidbody.m_SpinAngle = spinAngle; }

	TeamColor	GetTeam() const { return m_Team; }
	void		SetTeam( TeamColor val ) { m_Team = val; }

	CharacterClass GetCharacterClassName() { return m_ClassName; }

protected:	
// 	bool		m_IsAccelerating = false;
// 	bool		m_IsSpin = false;	
	
	TeamColor	m_Team = TeamColor::NO_TEAM;
	Rigidbody	m_Rigidbody;
	
	// 산소 및 추진체 관련
	float		m_Oxygen = DEFAULT_OXYGEN;
	float		m_Fuel = DEFAULT_FUEL;
	float		m_HP = DEFAULT_HP;
	DWORD		m_AccelerationStartTime = 0;
	float		m_SpinTime = 0.0f;

	CharacterClass m_ClassName = CharacterClass::NO_CLASS;
};

