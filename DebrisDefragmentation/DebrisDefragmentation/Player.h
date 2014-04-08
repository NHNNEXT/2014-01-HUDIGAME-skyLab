#pragma once
#include "DDObject.h"
#include "DDCamera.h"
#include "Character.h"

class Player :
	public DDObject
{
public:
	Player();
	virtual ~Player();

	CREATE_FUNC( Player );
	void Init();
	
	void Update( float dTime );
	void UpdateItSelf( float dTime );

	// 작성자 : 최경욱
	// 현재 바라보는 방향으로 가속도 부여
	void SetAcceleration();
	
	// 가속도 및 속도 0으로 변경
	void Stop();

	// 바라보는 방향 회전
	void RotateDicrection(float y, float x);

private:
	DDCamera*	m_Camera;
	Character*	m_Character;
	DDVECTOR3	m_Acceleration; // 자동으로 0, 0, 0으로 초기화 되나?
	DDVECTOR3	m_Velocity;

	bool		m_IsAccelerating;
	DWORD		m_AccelerationStart;
};

