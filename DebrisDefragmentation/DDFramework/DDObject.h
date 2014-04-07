#pragma once
#include "DDConfig.h"

class DDObject
{
public:
	DDObject();
	virtual ~DDObject();

	virtual void Release( );

	virtual void Render();
	virtual void Update(float dTime);
	
	DDObject* GetParent() { return m_pParent; }
	const std::list<DDObject*>& GetChildList() { return m_ChildList; }

	void SetParent( DDObject* object ) { m_pParent = object; }

	void AddChild( DDObject* object );
	void RemoveChild( DDObject* object );

	D3DXMATRIXA16 GetMatrix() const { return m_Matrix; }

	inline DDVECTOR3 GetPosition() { return m_Position; }
	inline float GetPositionX() const { return m_Position.x; }
	inline float GetPositionY() const { return m_Position.y; }
	inline float GetPositionZ() const { return m_Position.z; }
	
	inline DDVECTOR3 GetScale() { return m_Scale; }
	inline float GetScaleX() const { return m_Scale.x; }
	inline float GetScaleY() const { return m_Scale.y; }
	inline float GetScaleZ() const { return m_Scale.z; }
	
	inline DDVECTOR3 GetRotation() const { return m_Rotation; }
	inline float GetRotationX() const { return m_Rotation.x; }
	inline float GetRotationY() const { return m_Rotation.y; }
	inline float GetRotationZ() const { return m_Rotation.z; }
	
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

	inline bool IsVisible() const { return m_Visible; }

	void SetPosition( float x, float y, float z ) { m_Position = DDVECTOR3( x, y, z ); }
	void SetPosition( DDVECTOR3 point ) { m_Position = point; }

	void SetScale( float scaleX, float scaleY, float scaleZ ) {	m_Scale = DDVECTOR3( scaleX, scaleY, scaleZ );}
	void SetScale( DDVECTOR3 scale ) { m_Scale = scale; }

	void SetRotation( DDVECTOR3 rotation ) { m_Rotation = rotation; }
	void SetRotation( float rotationX, float rotationY, float rotationZ ) { m_Rotation = DDVECTOR3( rotationX, rotationY, rotationZ ); }
	
	void SetVisible( bool visible ) { m_Visible = visible; }

	void AffineTransfrom();
	void RenderChildNodes();

	virtual void UpdateItSelf( float dTime ) {};
	void UpdateChildNodes( float dTime );

	// z축 방향 벡터를 월드 좌표계 기준으로 반환
	DDVECTOR3 GetViewDirection();

protected:
	DDObject* m_pParent;
	std::list<DDObject*> m_ChildList;

	D3DXMATRIXA16	m_Matrix;
	D3DXMATRIXA16	m_MatrixTransform;
	DDVECTOR3		m_Position;
	DDVECTOR3		m_Rotation;
	DDVECTOR3		m_Scale;

	bool m_Visible;
};

