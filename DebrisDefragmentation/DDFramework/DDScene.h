#pragma once
#include "DDObject.h"
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
	// ���⼭ ���߿� skybox ����� �� �� ����(4.6 ��ȯ)
	//LPD3DXSPRITE	m_pSprite;
};

