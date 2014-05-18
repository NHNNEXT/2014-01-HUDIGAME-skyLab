#pragma once
#include "ClientObject.h"

struct MeshInfo
{
	LPD3DXMESH			m_pMesh = nullptr;
	LPDIRECT3DTEXTURE9* m_pMeshTexture = nullptr;
	D3DMATERIAL9*		m_pMeshMaterials = nullptr;
	DWORD				m_dwNumMaterials = 0L;	
};

enum class ModelType : int
{
	SKYBOX,
	EARTH,
	PLAYER_MODEL,
	DEBRIS,
	ISS
};

class DDModel :
	public ClientObject
{
public:
	DDModel();
	//DDModel( std::wstring filePath );
	virtual ~DDModel();

	//CREATE_OBJECT_WSTRING( DDModel, filePath );
	CREATE_OBJECT( DDModel );
	void SetModelMesh( MeshInfo* mi ) { m_MeshInfo = mi;	}

protected:
	virtual void RenderItSelf();


	// LPDIRECT3DDEVICE9	m_pD3DDevice = nullptr;
	MeshInfo*		m_MeshInfo = nullptr;
};

