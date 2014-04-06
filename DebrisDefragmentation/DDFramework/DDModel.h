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
	
	virtual void Render();
	virtual void Update( float dTime );

private: 
	bool initModel( wchar_t* path );	
	bool SetNormalVector();
	bool Cleanup();

private:	
	LPDIRECT3DDEVICE9	m_pD3DDevice;
	LPD3DXMESH			m_pMesh;
	D3DMATERIAL9*		m_pMeshMaterials;
	LPDIRECT3DTEXTURE9* m_pMeshTexture;
	DWORD				m_dwNumMaterials;

};

