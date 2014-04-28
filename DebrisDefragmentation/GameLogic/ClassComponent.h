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
	
	// 조심해!!
	// 가스가 떨어지면 멈춤, 값은 초기값 참고, 
	// CONSOLE에 LOG남겼는데 산소떨어지는 속도가 너무 빨라서 잘 안보임
	// 산소 및 추진체 관련
	int			m_Oxygen = DEFAULT_OXYGEN;
	int			m_Gas = DEFAULT_FUEL;
	int			m_HP = DEFAULT_HP;

	DWORD		m_AccelerationStartTime = 0;
	
};

