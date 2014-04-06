#pragma once

#include "DDConfig.h"

class DDRenderer
{
public:
	static DDRenderer* GetInstance();
	static void ReleaseInstance();

	bool Init( HWND hWnd );
	bool Release();

	bool Clear();
	bool Begin();
	bool End();

	LPDIRECT3D9 GetD3D() { return m_D3D; }
	LPDIRECT3DDEVICE9 GetDevice() { return m_D3DDevice; }
	LPD3DXSPRITE GetSprite() { return m_Sprite; }

private:
	DDRenderer();
	~DDRenderer();

	static DDRenderer* m_pInstance;

	LPDIRECT3D9				m_D3D;
	LPDIRECT3DDEVICE9		m_D3DDevice;
	LPD3DXSPRITE			m_Sprite;
	D3DPRESENT_PARAMETERS	m_D3DPresentParameters;
};

