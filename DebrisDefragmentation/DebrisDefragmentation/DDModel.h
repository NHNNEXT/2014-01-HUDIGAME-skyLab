#pragma once
#include "ClientObject.h"
#include "SkinnedMesh.h"
#include "Environment.h"
#include <dxerr.h>

struct MeshInfo
{
	// 조심해!!
	// 복사 생성자 ISS복사할 때 제대로 동작 안함 ㅠㅠ
	MeshInfo(){}
	MeshInfo( const MeshInfo& mi )
	{
		m_dwNumMaterials = mi.m_dwNumMaterials;
		HRESULT hr = FAILED( mi.m_pMesh->CloneMeshFVF(
			D3DXMESH_MANAGED,
			mi.m_pMesh->GetFVF(),  //이곳에 추가
			DDRenderer::GetInstance()->GetDevice(),
			&m_pMesh ) );

		if ( FAILED( hr ) )
		{
			// 		wchar_t szMsg[MAX_PATH] = L""; 
			// 		wprintf_s( szMsg, _countof( szMsg ), L"hr = %s Desc : %s", DXGetErrorString( hr ), DXGetErrorDescription( hr ) );
			printf( "Error: %s error description: %s\n", DXGetErrorString( hr ), DXGetErrorDescription( hr ) );
		}

		m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];
		m_pMeshTexture = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];
		for ( DWORD i = 0; i < m_dwNumMaterials; ++i )
		{
			m_pMeshMaterials[i] = mi.m_pMeshMaterials[i];
			m_pMeshTexture[i] = mi.m_pMeshTexture[i];
		}
	}

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
	PUSHPULL_EFFECT,
	ACCESS_POINT,
	SHUTTLE,
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
	bool			GetIncludeAnimation() const { return m_IncludeAnimation; }
	void			SetIncludeAnimation( bool val ) { m_IncludeAnimation = val; }

	void			SetMatrix( D3DXMATRIXA16* matrix ) { m_Matrix = *matrix; }
	void			AddDt( float dt ) { m_Dt += dt; }
	
	void			SetCharacterAnimationState( CharacterAnimState state );

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

	//D3DXMATRIXA16 m_Matrix; // temp
	float m_Dt = 0.0f;

	// 애니메이션 제어 용도
	float				m_AnimationPlayTime = 0.0f;
	CharacterAnimState	m_CurrentCharacterState = CharacterAnimState::NO_STATE;
};

