#pragma once

#include "DDObject.h"
#include "DDPoint.h"
#include "DDInputSystem.h"

class DDScene :
	public DDObject
{
public:
	DDScene();
	virtual ~DDScene();

	static DDScene* Create();

	virtual void Render();
	virtual void Update( float dTime );


protected:
	// 여기서 나중에 skybox 만들면 될 거 같음(4.6 성환)
	//LPD3DXSPRITE	m_pSprite;
};

