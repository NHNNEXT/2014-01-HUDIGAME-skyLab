#pragma once
#include "DDObject.h"
#include "DDModel.h"
#include "rigidbody.h"
#include "Avatar.h"

class DDCamera;
class Character;

// DDObject와 avatar를 다중상속하는 방식으로 변경
class Player :
	public DDObject
{
public:
	Player();
	Player( int playerId );
	virtual ~Player();

	//static Player* Create( int playerId );
	CREATE_OBJECT_INTEGER( Player , plyerId);
	void Init();	
	
	// 현재 바라보는 방향으로 가속도 부여
	void GoForward() { m_Avatar->_GoForward( GetViewDirection(), m_Rigidbody ); }

	// 가속도 및 속도 0으로 변경
	void Stop() { m_Avatar->_Stop( m_Rigidbody ); }

	// 바라보는 방향 회전
	void RotateDirection( float x, float y ) { m_Avatar->_RotateDirection( x, y, m_Rotation ); }

	// Getter Setter
	DDVECTOR3 GetVelocity() const { return m_Rigidbody.velocity; }
	DDVECTOR3 GetAcceleration() const { return m_Rigidbody.acceleration; }
	void SetVelocity( DDVECTOR3 val ) { m_Rigidbody.velocity = val; }	
	void SetAcceleration( DDVECTOR3 val ) { m_Rigidbody.acceleration = val; }



private:
	virtual void UpdateItSelf( float dTime );

	std::shared_ptr<Avatar>	m_Avatar; // shared_ptr기본 생성자에서 초기화
	DDCamera*	m_Camera = nullptr;	// agebreak : 플레이어가 카메라를 가지는것이 옳은건가??
	DDModel*	m_Character = nullptr;

	RIGIDBODY	m_Rigidbody;			// rigidbody 자체 초기화
};

