#pragma once

#include <d3dx9.h>

class Transform
{
public:
	Transform();
	~Transform();

	D3DXMATRIXA16 MatrixTransform();

	// local position 관련
	const D3DXVECTOR3 GetPosition() { return m_Position; }
	const float GetPositionX() const { return m_Position.x; }
	const float GetPositionY() const { return m_Position.y; }
	const float GetPositionZ() const { return m_Position.z; }
	void IncreasePosition( D3DXVECTOR3 position ) { m_Position += position; }
	void IncreasePositionX( float x ) { m_Position.x += x; }
	void IncreasePositionY( float y ) { m_Position.y += y; }
	void IncreasePositionZ( float z ) { m_Position.z += z; }
	void SetPosition( D3DXVECTOR3 position ) { m_Position = position; }
	void SetPosition( float x, float y, float z ) { m_Position = D3DXVECTOR3( x, y, z ); }

	// local rotation 관련
	const D3DXVECTOR3 GetRotation() const { return m_Rotation; }
	const float GetRotationX() const { return m_Rotation.x; }
	const float GetRotationY() const { return m_Rotation.y; }
	const float GetRotationZ() const { return m_Rotation.z; }
	void IncreaseRotation( D3DXVECTOR3 rotation ) { m_Rotation += rotation; }
	void IncreaseRotationX( float x ) { m_Rotation.x += x; }
	void IncreaseRotationY( float y ) { m_Rotation.y += y; }
	void IncreaseRotationZ( float z ) { m_Rotation.z += z; }
	void SetRotation( D3DXVECTOR3 rotation ) { m_Rotation = rotation; }
	void SetRotation( float rotationX, float rotationY, float rotationZ ) { m_Rotation = D3DXVECTOR3( rotationX, rotationY, rotationZ ); }

	// local scale 관련
	const D3DXVECTOR3 GetScale() { return m_Scale; }
	const float GetScaleX() const { return m_Scale.x; }
	const float GetScaleY() const { return m_Scale.y; }
	const float GetScaleZ() const { return m_Scale.z; }
	void IncreaseScale( D3DXVECTOR3 scale ) { m_Scale += scale; }
	void IncreaseScaleX( float x ) { m_Scale.x += x; }
	void IncreaseScaleY( float y ) { m_Scale.y += y; }
	void IncreaseScaleZ( float z ) { m_Scale.z += z; }
	void SetScale( D3DXVECTOR3 scale ) { m_Scale = scale; }
	void SetScale( float scaleX, float scaleY, float scaleZ ) { m_Scale = D3DXVECTOR3( scaleX, scaleY, scaleZ ); }
	void SetScale(float scale) { m_Scale = D3DXVECTOR3(scale, scale, scale); }	// agebreak : 이런 함수를 만들어 놓으면 유용함


private:

	// local coordinate
	D3DXVECTOR3		m_Position{ .0f, .0f, .0f };	// c++11에서 나온 균일한 중괄호 초기화라함.
	D3DXVECTOR3		m_Rotation{ .0f, .0f, .0f };
	D3DXVECTOR3		m_Scale{ 1.0f, 1.0f, 1.0f };

};

