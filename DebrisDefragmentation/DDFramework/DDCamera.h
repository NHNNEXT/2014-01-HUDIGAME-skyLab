#pragma once
#include "DDObject.h"
class DDCamera : public DDObject
{
public:
	DDCamera();
	virtual ~DDCamera();
	
	static DDCamera* Create();
	
// 	void SetLookatPoint( D3DXVECTOR3 lookatpoint ) { m_LookatPoint = lookatpoint; }
// 	void SetLookatPoint( float x, float y, float z ) { m_LookatPoint = DDVECTOR3( x, y, z ); }

private:
	virtual void RenderItSelf();

	D3DXVECTOR3 m_LookatPoint;
};

