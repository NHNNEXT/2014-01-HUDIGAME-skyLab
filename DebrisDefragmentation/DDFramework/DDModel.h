#pragma once
#include "DDObject.h"

class DDModel :
	public DDObject
{
public:
	DDModel();
	DDModel( wchar_t* filePath );
	DDModel( wchar_t* path, LPDIRECT3DDEVICE9 renderer );
	virtual ~DDModel();

	static DDModel* Create( wchar_t* filePath );	
	static DDModel* Create( wchar_t* filePath, LPDIRECT3DDEVICE9 renderer );

protected:
	bool initModel( wchar_t* path );	
	bool SetNormalVector();
	bool Cleanup();

	// LPDIRECT3DDEVICE9	m_pD3DDevice = nullptr;

	LPD3DXMESH			m_pMesh;/* = nullptr;*/
	LPDIRECT3DTEXTURE9* m_pMeshTexture;/* = nullptr;*/
	D3DMATERIAL9*		m_pMeshMaterials;/* = nullptr;*/
	DWORD				m_dwNumMaterials;/* = 0L;*/

private:
	virtual void RenderItSelf();
};

