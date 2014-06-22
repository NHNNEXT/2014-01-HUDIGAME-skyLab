#pragma once
#include "ClientObject.h"
#include "DDModel.h"
#include "rigidbody.h"
#include "ClassComponent.h"
#include "CollisionBox.h"

/// 전방 선언
class DDCamera;
class CharacterModel;

// avatar를 멤버변수로 컴퍼짓함 
class Player :
	public ClientObject
{
public:
	Player();
	Player( int playerId, CharacterClass characterClass = CharacterClass::STRIKER );
	virtual ~Player();

	//static Player* Create( int playerId );
	CREATE_OBJECT_INTEGER( Player , plyerId );
	void Init();	
	void InitRigidBody();
	
	void		SetTeam( TeamColor color ) { m_Team = color; }
	TeamColor	GetTeam() { return m_Team; }

	// 현재 바라보는 방향으로 가속도 부여
	void Move( const D3DXVECTOR3& direction );

	// 가속도 및 속도 0으로 변경
	void Stop();

	// 바라보는 방향 회전
	void LookAt( float x, float y, float z );

	const float			GetMass() const { return m_Rigidbody.m_Mass; }
	const D3DXVECTOR3	GetAcceleration() const { return m_Rigidbody.m_Acceleration; }
	const D3DXVECTOR3	GetVelocity() const { return m_Rigidbody.m_Velocity * m_SpeedConstant; } // 순간 가속을 할 수 있으므로 상수를 곱해서 반환 - 내부에서 직접 참조하면 안 되는데
	const D3DXVECTOR3	GetSpinAxis() const { return m_Rigidbody.m_SpinAxis; }
	const float			GetSpinAngularVelocity() const { return m_Rigidbody.m_SpinAngularVelocity; }

	void	SetMass( float mass ) { m_Rigidbody.m_Mass = mass; }
	void	SetAcceleration( D3DXVECTOR3 accel ) { m_Rigidbody.m_Acceleration = accel; }
	void	SetVelocity( D3DXVECTOR3 velocity ) { m_Rigidbody.m_Velocity = velocity; }
	void	SetSpinAxis( D3DXVECTOR3 spinAxis ) { m_Rigidbody.m_SpinAxis = spinAxis; }
	void	SetSpinAngularVelocity( float spinAngle ) { m_Rigidbody.m_SpinAngularVelocity = spinAngle; }

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

	bool	IsAccelerating() const { return m_Rigidbody.m_IsAccelerating; }
	void	SetIsAccelerating( bool val ) { m_Rigidbody.m_IsAccelerating = val; }

	DWORD	GetAccelerationStartTime() const { return m_AccelerationStartTime; }
	void	SetAccelerationStartTime( DWORD val ) { m_AccelerationStartTime = val; }

	// Getter Setter
	ClassComponent* GetClassComponent() { return m_ClassComponent.get(); }
	Rigidbody*		GetRigidbody() { return &m_Rigidbody; }

	void ChangeClass( CharacterClass characterClass );

	float GetGas() { return m_ClassComponent->GetFuel(); }
	float GetOxygen() { return m_ClassComponent->GetOxygen(); }

private:
	virtual void RenderItSelf();
	virtual void UpdateItSelf( float dTime );

	void InitCollisionBox();
	void DrawCollisionBox();

	int								m_PlayerId;
	std::shared_ptr<ClassComponent>	m_ClassComponent; // shared_ptr기본 생성자에서 초기화
	TeamColor						m_Team = TeamColor::NO_TEAM;
	Rigidbody						m_Rigidbody;

	DWORD		m_AccelerationStartTime = 0;
	float		m_SpinTime = 0.0f;
	bool		m_MovingFlag = true;
	float		m_SpeedConstant = DEFAULT_PLAYER_SPEED;
	float		m_LastHealingEffectTime = HEALING_LIFETIME;

	DDModel*	m_CharacterModel = nullptr;

	CollisionBox	m_CollisionBox;
};

