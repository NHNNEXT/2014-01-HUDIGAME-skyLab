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
	// 현재 바라보는 방향으로 가속도 부여
	void GoForward( D3DXVECTOR3 viewDirection, Rigidbody& rigidbody );

	// 가속도 및 속도 0으로 변경
	void Stop( Rigidbody& rigidbody );

	// 바라보는 방향 회전
	void LookAt( float x, float y, D3DXVECTOR3& rotation );

	int		GetAvatarId() const { return m_AvatarId; }
	DWORD	GetAccelerationStartTime() const { return m_AccelerationStartTime; }
	void	SetAvatarId( int val ) { m_AvatarId = val; }
	void	SetAccelerationStartTime( DWORD val ) { m_AccelerationStartTime = val; }

	bool	IsAccelerating() const { return m_IsAccelerating; }
	void	SetIsAccelerating( bool val ) { m_IsAccelerating = val; }
	
	
protected:
	int			m_AvatarId = -1;
	bool		m_IsAccelerating = false;
	
	float		m_Oxygen = .0f;
	float		m_Gas = .0f;
	
	DWORD		m_AccelerationStartTime = 0;
	
};

