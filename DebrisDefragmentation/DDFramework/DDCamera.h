#pragma once
#include "DDObject.h"
class DDCamera : public DDObject
{
public:
	DDCamera();
	virtual ~DDCamera();
	
	CREATE_FUNC( DDCamera );
	//static DDCamera* Create();
	
// 	void SetLookatPoint( DDVECTOR3 lookatpoint ) { m_LookatPoint = lookatpoint; }
// 	void SetLookatPoint( float x, float y, float z ) { m_LookatPoint = DDVECTOR3( x, y, z ); }

private:
	virtual void RenderItSelf();

	DDVECTOR3 m_LookatPoint;
};

