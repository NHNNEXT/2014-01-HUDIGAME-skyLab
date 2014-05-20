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

	static std::shared_ptr<ClassComponent> Create( CharacterClass className );

	// 사용자들이 사용하는 스킬들!
	bool	GoForward( D3DXVECTOR3 viewDirection ); // 현재 바라보는 방향으로 가속도 부여
	void	Stop();	// 가속도 및 속도 0으로 변경	

	void	ResetStatus();

	// 바라보는 방향으로 몸을 회전 turn body to viewing direction 
	void	TurnBody( Transform& tr, float x, float y, float z ) { tr.SetRotation( x, y, z ); }

	// 적절한 스킬 사용 함수를 호출한다.
	virtual bool UseSkill( ClassSkill skill, int id, const D3DXVECTOR3& direction ) = 0;

	bool		SkillPush( int id, const D3DXVECTOR3& direction );
	bool		SkillShareFuel( int id, const D3DXVECTOR3& direction );
	bool		SkillOccupy( int id, const D3DXVECTOR3& direction );
	bool		SkillDestroy( int id, const D3DXVECTOR3& direction );
	/*bool		SkillBuildDispenser( int id, const D3DXVECTOR3& direction );*/

	// 기존의 setAcceleration. 이름이 acceleration 값을 set하는 함수랑 같아서 변경함.
	void	AddForce( const D3DXVECTOR3 &direction );

	DWORD	GetAccelerationStartTime() const { return m_AccelerationStartTime; }
	void	SetAccelerationStartTime( DWORD val ) { m_AccelerationStartTime = val; }

	bool	IsAccelerating() const { return m_Rigidbody.m_IsAccelerating; }
	void	SetIsAccelerating( bool val ) { m_Rigidbody.m_IsAccelerating = val; }

	void	SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity );

	// 현재 자전에 추가 자전 요소 추가 : 차차 구현
	void	AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity );

	// 자전 금지
	void	StopSpin();

	void	SetSpinnigFlag( bool flag ) { m_Rigidbody.m_IsSpin = flag; }
	bool	IsSpinning() { return m_Rigidbody.m_IsSpin; }
	void	AddSpinTime( float dt ) { m_SpinTime += dt; }
	float	GetSpinTime() { return m_SpinTime; }
	void	SetSpinTime( float time ) { m_SpinTime = time; }
	
	float	GetFuel() const { return m_Fuel; }
	void	SetFuel( float val ) { m_Fuel = val < 0.0f ? 0.0f : val; }

	float	GetOxygen() const { return m_Oxygen; }
	void	SetOxygen( float val ){ m_Oxygen = val < 0.0f ? 0.0f : val; }
	void	IncreaseOxygen( float val ) { m_Oxygen = ( m_Oxygen + val < 0 ) ? 0.0f : ( m_Oxygen + val ); }
	void	IncreaseFuel( float val ) { m_Fuel = ( m_Fuel + val < 0 ) ? 0.0f : ( m_Fuel + val ); }

	float	GetHP() const { return m_HP; }
	void	SetHP( float val ) { m_HP = val; }

	bool	IsAlive() { return ( m_HP > 0.0f ) ? true : false; }
	bool	UseFuel( float fuelUse );
	bool	UseOxygen( float oxygenUse );

	void	SetGlobalCooldown( float time ) { m_GlobalCooldown = ( m_GlobalCooldown < time ) ? time : m_GlobalCooldown; }
	float	GetGlobalCooldown() { return m_GlobalCooldown; }

	// 주기적으로 처리해야 하는 일들
	// 예를 들어 산소량 감소와 같은 일을 처리 
	void	Update( float dt );

// 	Rigidbody	GetRigidbody() { return m_Rigidbody; }
// 	void		SetRigidbody( Rigidbody val ) { m_Rigidbody = val; }

	const float&		GetMass() const { return m_Rigidbody.m_Mass; }
	const D3DXVECTOR3&	GetAcceleration() const { return m_Rigidbody.m_Acceleration; }
	const D3DXVECTOR3&	GetVelocity() const { return m_Rigidbody.m_Velocity * m_SpeedConstant; } // 순간 가속을 할 수 있으므로 상수를 곱해서 반환 - 내부에서 직접 참조하면 안 되는데
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
	void		SetCooldown( ClassSkill skillType );

	TeamColor	m_Team = TeamColor::NO_TEAM;
	Rigidbody	m_Rigidbody;
	
	// 산소 및 추진체 관련
	float		m_Oxygen = DEFAULT_OXYGEN;
	float		m_Fuel = DEFAULT_FUEL;
	float		m_HP = DEFAULT_HP;
	DWORD		m_AccelerationStartTime = 0;
	float		m_SpinTime = 0.0f;
	float		m_SpeedConstant = 1.0f;

	CharacterClass m_ClassName = CharacterClass::NO_CLASS;

	float		m_GlobalCooldown = 0.0f;
	std::array<float, TOTAL_SKILL_NUMBER> m_CooldownTable;

	virtual void DoPeriodWork( float dTime ) { UNREFERENCED_PARAMETER( dTime ); }
};

