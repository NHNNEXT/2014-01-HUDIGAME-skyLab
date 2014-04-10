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
	
protected:
	// ���⼭ ���߿� skybox ����� �� �� ����(4.6 ��ȯ)
	//LPD3DXSPRITE	m_pSprite;

private:
	virtual void RenderItSelf();
};

