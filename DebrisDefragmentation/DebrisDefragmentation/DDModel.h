#pragma once
#include "ClientObject.h"
#include "SkinnedMesh.h"

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
	PLAYER_MODEL_ANIMATION,
	DEBRIS,
	ISS,
	DISPENSER,
	SPACE_MINE,
	PUSHPULL_EFFECT
};

class DDModel :
	public ClientObject
{
public:
	DDModel();
	virtual ~DDModel();
	
	CREATE_OBJECT( DDModel );
	bool			InitFX( std::wstring filepath );
	void			SetModelMesh( MeshInfo* mi );
	void			SetModelSkinnedMesh( SkinnedMesh* mi );

	void			DrawMesh();
	void			DrawAnimationMesh();

	void			SetMatrix( D3DXMATRIXA16* matrix ) { m_Matrix = *matrix; }
	void			AddDt( float dt ) { m_Dt += dt; }
	
	// 셰이더에서 사용할 변수값 셋팅
	virtual void	SetupFX() {}

protected:
	virtual void	RenderItSelf();

	bool			m_IncludeAnimation = false;
	MeshInfo*		m_MeshInfo = nullptr;
	SkinnedMesh*	m_SkinnedMeshInfo = nullptr;
	bool			m_UseShader = false;
	LPD3DXEFFECT	m_pEffect = nullptr;
	LPDIRECT3DVERTEXDECLARATION9 m_pDecl = nullptr;

	D3DXMATRIXA16 m_Matrix; // temp
	float m_Dt = 0.0f;
};

