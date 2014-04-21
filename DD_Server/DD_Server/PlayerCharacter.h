#pragma once

#include "GameConfig.h"

class PlayerCharacter
{
	// 아무래도 임시 파일이 될 듯
	// 클라이언트의 로직 부분을 아예 분리해서 서버에서도 공유할 수 있도록 해야
	// 로직도 두 부분으로 나눌 수 있어야 함 
	// 게임 내 판정이 필요한 것은 모두 서버에서 관리하고
	// 캐릭터들의 움직임을 계산하는 부분은 클라에서도 동시에 계산
public:
	PlayerCharacter( int playerId );
	~PlayerCharacter();

	void Update( float dTime );

	void SetPosition( float x, float y, float z ) { m_Position = D3DXVECTOR3( x, y, z ); }
	void SetScale( float scaleX, float scaleY, float scaleZ ) { m_Scale = D3DXVECTOR3( scaleX, scaleY, scaleZ ); }
	void SetRotation( float rotationX, float rotationY, float rotationZ ) { m_Rotation = D3DXVECTOR3( rotationX, rotationY, rotationZ ); }

	void SetAcceleration();
	void Stop();
	void RotateDicrection( float y, float x );

	// player 상태 가져오기
	int GetPlayerId() { return m_PlayerId; }
	D3DXVECTOR3 GetPosition() { return m_Position; }
	D3DXVECTOR3 GetScale() { return m_Scale; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetVelocity( ) { return m_Velocity; }

private:
	D3DXVECTOR3 GetViewDirection();

	int				m_PlayerId = -1;

	D3DXVECTOR3		m_Position;
	D3DXVECTOR3		m_Rotation;
	D3DXVECTOR3		m_Scale;

	D3DXVECTOR3		m_Acceleration; 
	D3DXVECTOR3		m_Velocity;

	bool		m_IsAccelerating;
	DWORD		m_AccelerationStart;
};

