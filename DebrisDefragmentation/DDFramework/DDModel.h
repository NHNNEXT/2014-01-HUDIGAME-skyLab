#pragma once
#include "DDObject.h"

class DDModel :
	public DDObject
{
public:
	DDModel();
	DDModel( wchar_t* filePath );
	virtual ~DDModel();

	static DDModel* Create( wchar_t* filePath );	

protected:
	bool initModel( wchar_t* path );	
	bool SetNormalVector();
	bool Cleanup();

	LPDIRECT3DDEVICE9	m_pD3DDevice;

	LPD3DXMESH			m_pMesh;
	LPDIRECT3DTEXTURE9* m_pMeshTexture;
	D3DMATERIAL9*		m_pMeshMaterials;
	DWORD				m_dwNumMaterials;

private:
	virtual void RenderItSelf();
};

