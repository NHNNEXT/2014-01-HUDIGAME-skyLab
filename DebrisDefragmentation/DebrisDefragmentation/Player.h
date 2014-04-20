#pragma once
#include "DDObject.h"
#include "DDModel.h"

class DDCamera;
class Character;

class Player :
	public DDObject
{
public:
	Player();
	Player( int playerId );
	virtual ~Player();

	//static Player* Create( int playerId );
	CREATE_FUNC_INTEGER( Player , plyerId);
	void Init();	

	// 작성자 : 최경욱
	// 현재 바라보는 방향으로 가속도 부여
	// 함수 이름 바꿔야 할 것 같음 GoForward 같은 걸로
	// SetAcceleration은 m_Acc값 get, set할 때 사용해야할듯
	void SetAcceleration();
	
	// 가속도 및 속도 0으로 변경
	void Stop();

	// 바라보는 방향 회전
	void RotateDicrection(float x, float y);

	DDVECTOR3 GetVelocity() const { return m_Velocity; }
	void SetVelocity( DDVECTOR3 val ) { m_Velocity = val; }
	
	// 임시로 이름을 SetAccel, GetAccel등으로 함 추후에 SetAcceleration과 함께 수정 요
	// 4.15 김성환
	DDVECTOR3 GetAccel() const { return m_Acceleration; }
	void SetAccel( DDVECTOR3 val ) { m_Acceleration = val; }


	int GetPlayerId() const { return m_PlayerId; }
	void SetPlayerId( int val ) { m_PlayerId = val; }

private:
	virtual void UpdateItSelf( float dTime );

	int			m_PlayerId = -1;
	DDCamera*	m_Camera = nullptr;
	DDModel*	m_Character = nullptr;
	DDVECTOR3	m_Acceleration{ .0f, .0f, .0f }; 
	DDVECTOR3	m_Velocity{ .0f, .0f, .0f };
	bool		m_IsAccelerating = 0;
	DWORD		m_AccelerationStart = 0;
};

