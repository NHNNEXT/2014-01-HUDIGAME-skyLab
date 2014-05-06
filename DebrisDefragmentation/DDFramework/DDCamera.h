#pragma once
#include "DDObject.h"
class DDCamera : public DDObject
{
public:
	DDCamera();
	virtual ~DDCamera();

	CREATE_OBJECT( DDCamera );	
	
	// following object가 있으면 임베디드카메라를 끈다.
	DDObject*	GetFollowingObject() const { return m_FollowingObject; }
	void		SetFollowingObject( DDObject* val ) { m_FollowingObject = val; m_EmbeddedCamera = false; }

	void		SetAspectRatio(float width, float height);

// 	void SetLookatPoint( DDVECTOR3 lookatpoint ) { m_LookatPoint = lookatpoint; }
// 	void SetLookatPoint( float x, float y, float z ) { m_LookatPoint = DDVECTOR3( x, y, z ); }

protected:
	virtual void RenderItSelf();
	DDObject*	m_FollowingObject = nullptr;
	DDVECTOR3	m_LookatPoint;
	bool		m_EmbeddedCamera = true;

private:
	void		SetAspectRatio();

	float WindowsWidth = 0;
	float WindowsHeight = 0;
};

