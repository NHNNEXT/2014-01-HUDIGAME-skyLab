#pragma once
#include "DDObject.h"
class DDCamera : public DDObject
{
public:
	DDCamera();
	virtual ~DDCamera();
	
	static DDCamera* Create();

	virtual void Render();
	virtual void Update( float dTime );

	void SetLookatPoint( D3DXVECTOR3 lookatpoint ) { m_LookatPoint = lookatpoint; };
	void SetLookatPoint( float x, float y, float z ) {};

private : 
	D3DXVECTOR3 m_LookatPoint;
};

