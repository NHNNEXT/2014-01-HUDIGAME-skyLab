/*
	게임 내부에서 인터랙션이 발생하는 모든 것들의 최상위 클래스
	위치와 크기, 회전 등의 정보를 가지고 있다. (DDFramework의 Object와 비슷) 
	움직임은 하위 클래스에서 구현할 것
	2014. 4. 21 최경욱
*/

#pragma once

#include "GameConfig.h"

class Actor
{
public:
	Actor();
	virtual ~Actor();

	void Update( float dTime );

	void SetPosition( float x, float y, float z ) { m_Position = D3DXVECTOR3( x, y, z ); }
	void SetScale( float scaleX, float scaleY, float scaleZ ) { m_Scale = D3DXVECTOR3( scaleX, scaleY, scaleZ ); }
	void SetRotation( float rotationX, float rotationY, float rotationZ ) { m_Rotation = D3DXVECTOR3( rotationX, rotationY, rotationZ ); }

protected:
	D3DXVECTOR3		m_Position{ 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3		m_Rotation{ 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3		m_Scale{ 1.0f, 1.0f, 1.0f };

private:
	virtual void UpdateItSelf( float dTime ) { UNREFERENCED_PARAMETER( dTime ); }
};

