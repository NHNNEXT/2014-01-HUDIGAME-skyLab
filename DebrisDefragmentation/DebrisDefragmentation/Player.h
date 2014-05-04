#pragma once
#include "DDObject.h"
#include "DDModel.h"
#include "rigidbody.h"
#include "ClassComponent.h"
#include "CollisionBox.h"

/// 전방 선언
class DDCamera;
class CharacterModel;

// avatar를 멤버변수로 컴퍼짓함 
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
	void GoForward() { m_CharacterClass->GoForward( GetViewDirection(), m_RigidBody ); }

	// 가속도 및 속도 0으로 변경
	void Stop() { m_CharacterClass->Stop( m_RigidBody ); }

	void SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity );

	// 현재 자전에 추가 자전 요소 추가 : 차차 구현
	void AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity );

	// 자전 금지
	void StopSpin();

	// 바라보는 방향 회전
	//void LookAt( float x, float y, float z ) { m_CharacterClass->LookAt( m_HeadDirection, x, y, z ); }

	void LookAt( float x, float y, float z );
	void TurnBody( float x, float y, float z );

	// Getter Setter
	DDVECTOR3 GetVelocity() const { return m_RigidBody.m_Velocity; }
	DDVECTOR3 GetAcceleration() const { return m_RigidBody.m_Acceleration; }
	void SetVelocity( DDVECTOR3 val ) { m_RigidBody.m_Velocity = val; }	
	void SetAcceleration( DDVECTOR3 val ) { m_RigidBody.m_Acceleration = val; }
	//DDVECTOR3 GetHeadDirection() { return m_HeadDirection; }
	int GetGas() { return m_CharacterClass->GetGas(); }
	int GetOxygen() { return m_CharacterClass->GetOxygen(); }

private:
	virtual void RenderItSelf();
	virtual void UpdateItSelf( float dTime );

	void InitCollisionBox();
	void DrawCollisionBox();

	unsigned int					m_PlayerId;
	std::shared_ptr<ClassComponent>	m_CharacterClass; // shared_ptr기본 생성자에서 초기화
	DDModel*						m_CharacterModel = nullptr;
	//DDCamera*						m_Camera = nullptr;		

	//DDVECTOR3	m_HeadDirection{ .0f, .0f, .0f };
	Rigidbody		m_RigidBody;			// rigidbody 자체 초기화
	CollisionBox	m_CollisionBox;
};

