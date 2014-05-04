#pragma once
#include "GameConfig.h"

//전방선언
struct Rigidbody;

class ClassComponent
{
public:
	ClassComponent();
	~ClassComponent();

	CREATE_FUNC( ClassComponent );

	// 작성자 : 최경욱	
	// 
	void	GoForward( D3DXVECTOR3 viewDirection, Rigidbody& rigidbody ); // 현재 바라보는 방향으로 가속도 부여
	void	Stop( Rigidbody& rigidbody );	// 가속도 및 속도 0으로 변경	

	// 바라보는 방향으로 몸을 회전 turn body to viewing direction 04.27김성환
	void	TurnBody( D3DXVECTOR3& rotation, float x, float y, float z ) { rotation = D3DXVECTOR3( x, y, z ); } 

	DWORD	GetAccelerationStartTime() const { return m_AccelerationStartTime; }
	void	SetAccelerationStartTime( DWORD val ) { m_AccelerationStartTime = val; }

	bool	IsAccelerating() const { return m_IsAccelerating; }
	void	SetIsAccelerating( bool val ) { m_IsAccelerating = val; }

	void	SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity, Rigidbody& rigidbody );

	// 현재 자전에 추가 자전 요소 추가 : 차차 구현
	void	AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity, Rigidbody& rigidbody );

	// 자전 금지
	void	StopSpin( Rigidbody& rigidbody );

	void	SetSpinnigFlag( bool flag ) { m_IsSpin = flag; }
	bool	IsSpinning() { return m_IsSpin; }
	void	AddSpinTime( float dt ) { m_SpinTime += dt; }
	float	GetSpinTime() { return m_SpinTime; }
	void	SetSpinTime( float time ) { m_SpinTime = time; }
	
	int		GetGas() const { return m_Gas; }
	void	SetGas( int val ) { m_Gas = val; }

	int		GetOxygen() const { return m_Oxygen; }
	void	SetOxygen( int val ) { m_Oxygen = val; }
	void	IncreaseOxygen( int val ) { m_Oxygen += val; }

	bool	IsAlive() { return ( m_HP > 0 ) ? true : false; }
	bool	CheckRemainGas( int gasWillBeUsed );
	bool	CheckRemainOxygen();

protected:	
	bool		m_IsAccelerating = false;
	bool		m_IsSpin = false;
	
	
	// 산소 및 추진체 관련
	int			m_Oxygen = DEFAULT_OXYGEN;
	int			m_Gas = DEFAULT_FUEL;
	int			m_HP = DEFAULT_HP;

	DWORD		m_AccelerationStartTime = 0;
	float		m_SpinTime = 0.0f;
};

