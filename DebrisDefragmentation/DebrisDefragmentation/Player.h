#pragma once
#include "DDObject.h"
#include "DDModel.h"
#include "rigidbody.h"
#include "Avatar.h"

class DDCamera;
class Character;

// DDObject와 avatar를 다중상속하는 방식으로 변경
class Player :
	public DDObject,
	public Avatar
{
public:
	Player();
	Player( int playerId );
	virtual ~Player();

	//static Player* Create( int playerId );
	CREATE_FUNC_INTEGER( Player , plyerId);
	void Init();	
	
	// 현재 바라보는 방향으로 가속도 부여
	void GoForward() { Avatar::_GoForward( GetViewDirection(), m_Rigidbody ); }

	// 가속도 및 속도 0으로 변경
	void Stop() { Avatar::_Stop( m_Rigidbody ); }

	// 바라보는 방향 회전
	void RotateDicrection( float x, float y ) { Avatar::_RotateDicrection( x, y, m_Rotation ); }

	// Getter Setter
	DDVECTOR3 GetVelocity() const { return m_Rigidbody.velocity; }
	DDVECTOR3 GetAcceleration() const { return m_Rigidbody.acceleration; }
	void SetVelocity( DDVECTOR3 val ) { m_Rigidbody.velocity = val; }	
	void SetAcceleration( DDVECTOR3 val ) { m_Rigidbody.acceleration = val; }



private:
	virtual void UpdateItSelf( float dTime );

	DDCamera*	m_Camera = nullptr;
	DDModel*	m_Character = nullptr;

	RIGIDBODY	m_Rigidbody;
};

