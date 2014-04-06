#pragma once
#include "DDConfig.h"

class DDObject
{
public:
	DDObject();
	virtual ~DDObject();

	virtual void Render();
	virtual void Update(float dTime);
	
	DDObject* GetParent() { return m_pParent; }
	const std::list<DDObject*>& GetChildList() { return m_ChildList; }

	void SetParent( DDObject* object ) { m_pParent = object; }

	void AddChild( DDObject* object );
	void RemoveChild( DDObject* object );

	inline D3DXMATRIXA16 GetMatrix() const { return m_Matrix; }

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
	
	inline bool IsVisible() const { return m_Visible; }

	void SetPosition( float x, float y, float z ) { m_Position = DDVECTOR3( x, y, z ); }
	void SetPosition( DDVECTOR3 point ) { m_Position = point; }

	void SetScale( float scaleX, float scaleY, float scaleZ ) {	m_Scale = DDVECTOR3( scaleX, scaleY, scaleZ );}
	void SetScale( DDVECTOR3 scale ) { m_Scale = scale; }

	void SetRotation( DDVECTOR3 rotation ) { m_Rotation = rotation; }
	void SetRotation( float rotationX, float rotationY, float rotationZ ) { m_Rotation = DDVECTOR3( rotationX, rotationY, rotationZ ); }
	
	void SetVisible( bool visible ) { m_Visible = visible; }

protected:
	void AffineTransfrom();
	void RenderChildNodes();
	void UpdateChildNodes(float dTime);

protected:
	DDObject* m_pParent;
	std::list<DDObject*> m_ChildList;

	D3DXMATRIXA16	m_Matrix;
	DDVECTOR3		m_Position;
	DDVECTOR3		m_Rotation;
	DDVECTOR3		m_Scale;

	//D3DXVECTOR3 	m_Center;
	
	bool m_Visible;
};

