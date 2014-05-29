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
	ISS,
	DISPENSER
};

class DDModel :
	public ClientObject
{
public:
	DDModel();
	virtual ~DDModel();
	
	CREATE_OBJECT( DDModel );
	bool			InitFX( std::wstring filepath );
	void			SetModelMesh( MeshInfo* mi ) { m_MeshInfo = mi;	}
	
	// 셰이더에서 사용할 변수값 셋팅
	virtual void	SetupFX() {}

protected:
	virtual void	RenderItSelf();

	MeshInfo*		m_MeshInfo = nullptr;
	bool			m_UseShader = false;
	LPD3DXEFFECT	m_pEffect = nullptr;
	LPDIRECT3DVERTEXDECLARATION9 m_pDecl = nullptr;
};

