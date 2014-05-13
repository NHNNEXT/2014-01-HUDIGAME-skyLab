#pragma once
#include "ClientObject.h"
class DDCamera : public ClientObject
{
public:
	DDCamera();
	virtual ~DDCamera();

	CREATE_OBJECT( DDCamera );	
	
	// following object가 있으면 임베디드카메라를 끈다.
	ClientObject*	GetFollowingObject() const { return m_FollowingObject; }
	void		SetFollowingObject( ClientObject* val ) { m_FollowingObject = val; m_FirstPersonCamera = true; }

	void		SetAspectRatio( float width, float height );

// 	void SetLookatPoint( DDVECTOR3 lookatpoint ) { m_LookatPoint = lookatpoint; }
// 	void SetLookatPoint( float x, float y, float z ) { m_LookatPoint = DDVECTOR3( x, y, z ); }

protected:
	virtual void RenderItSelf();
	ClientObject*	m_FollowingObject = nullptr;
	DDVECTOR3	m_LookatPoint;
	bool		m_FirstPersonCamera = false;
		
private:
	void		SetAspectRatio();

	float WindowsWidth = 0;
	float WindowsHeight = 0;
};

