#pragma once
#include "DDConfig.h"

class DDObject
{
public:
	DDObject();
	virtual ~DDObject();

	virtual void Release( );

	
	const DDObject* GetParent() { return m_pParent; }
	const std::list<std::shared_ptr<DDObject>>& GetChildList() { return m_ChildList; }
	
	void AddChild( DDObject* object );
	void RemoveChild( DDObject* object );

	D3DXMATRIXA16 GetMatrix() const { return m_Matrix; }

	const DDVECTOR3 GetPosition() { return m_Position; }
	const float GetPositionX() const { return m_Position.x; }
	const float GetPositionY() const { return m_Position.y; }
	const float GetPositionZ() const { return m_Position.z; }
	
	const DDVECTOR3 GetScale() { return m_Scale; }
	const float GetScaleX() const { return m_Scale.x; }
	const float GetScaleY() const { return m_Scale.y; }
	const float GetScaleZ() const { return m_Scale.z; }
	
	const DDVECTOR3 GetRotation() const { return m_Rotation; }
	const float GetRotationX() const { return m_Rotation.x; }
	const float GetRotationY() const { return m_Rotation.y; }
	const float GetRotationZ() const { return m_Rotation.z; }
	
	void IncreasePosition(DDVECTOR3 position) { m_Position += position; }
	void IncreasePositionX(float x) { m_Position.x += x; }
	void IncreasePositionY(float y) { m_Position.y += y; }
	void IncreasePositionZ(float z) { m_Position.z += z; }

	void IncreaseScale(DDVECTOR3 scale) { m_Scale += scale; }
	void IncreaseScaleX(float x) { m_Scale.x += x; }
	void IncreaseScaleY(float y) { m_Scale.y += y; }
	void IncreaseScaleZ(float z) { m_Scale.z += z; }

	void IncreaseRotation(DDVECTOR3 rotation) { m_Rotation += rotation; }
	void IncreaseRotationX(float x) { m_Rotation.x += x; }
	void IncreaseRotationY(float y) { m_Rotation.y += y; }
	void IncreaseRotationZ(float z) { m_Rotation.z += z; }

	bool IsVisible() const { return m_Visible; }

	void SetPosition( float x, float y, float z ) { m_Position = DDVECTOR3( x, y, z ); }
	void SetPosition( DDVECTOR3 point ) { m_Position = point; }

	void SetScale( float scaleX, float scaleY, float scaleZ ) {	m_Scale = DDVECTOR3( scaleX, scaleY, scaleZ );}
	void SetScale( DDVECTOR3 scale ) { m_Scale = scale; }

	void SetRotation( DDVECTOR3 rotation ) { m_Rotation = rotation; }
	void SetRotation( float rotationX, float rotationY, float rotationZ ) { m_Rotation = DDVECTOR3( rotationX, rotationY, rotationZ ); }
	
	void SetVisible( bool visible ) { m_Visible = visible; }

	

	// z�� ���� ���͸� ���� ��ǥ�� �������� ��ȯ
	DDVECTOR3 GetViewDirection();

	// NVI Wrapper (�񰡻� �������̽�)
	void Render();
	void Update( float dTime );


protected:
	void SetParent( DDObject* object ) { m_pParent = object; }

	DDObject* m_pParent;
	std::list<std::shared_ptr<DDObject>> m_ChildList;

	D3DXMATRIXA16	m_Matrix;			// world coordinate
	D3DXMATRIXA16	m_MatrixTransform;	// local coordinate
	D3DXMATRIXA16	m_MatrixRotation;
	DDVECTOR3		m_Position;
	DDVECTOR3		m_Rotation;
	DDVECTOR3		m_Scale;

	bool m_Visible;

private : 
	// NVI �Լ� ����
	void AffineTransfrom();
	void RenderChildNodes();
	void UpdateChildNodes( float dTime );

	// NVI virtual function
	virtual void RenderItSelf() {};
	virtual void UpdateItSelf( float dTime ) {};
};

