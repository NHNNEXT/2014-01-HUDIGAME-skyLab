#pragma once

#include "d3dx9.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif

enum METHOD
{
	D3DINDEXEDHLSLVS,
	NONE
};

// 상속받고 변환이 누적된 함수를 저장할 변수를 추가
struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
};

// 각각의 메시를 저장하는 곳
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	// 텍스처 배열에 대한 포인터
	// 텍스처가 명확하지 않으면 NULL
	LPDIRECT3DTEXTURE9* ppTextures;

	// SkinMesh info             
	LPD3DXMESH pOrigMesh;
	LPD3DXATTRIBUTERANGE pAttributeTable;
	DWORD NumAttributeGroups;
	DWORD NumInfl;
	LPD3DXBUFFER pBoneCombinationBuf;
	D3DXMATRIX** ppBoneMatrixPtrs;
	D3DXMATRIX* pBoneOffsetMatrices;
	DWORD NumPaletteEntries;
	bool UseSoftwareVP;
	DWORD iAttributeSW;     // used to denote the split between SW and HW if necessary for non-indexed skinning
};

class AllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	STDMETHOD( CreateFrame )( THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame );
	STDMETHOD( CreateMeshContainer )( THIS_
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer );
	STDMETHOD( DestroyFrame )( THIS_ LPD3DXFRAME pFrameToFree );
	STDMETHOD( DestroyMeshContainer )( THIS_ LPD3DXMESHCONTAINER pMeshContainerBase );

	AllocateHierarchy()
	{
	}

private:
	HRESULT AllocateName( LPCSTR Name, LPSTR* pNewName );
	HRESULT GenerateSkinnedMesh( IDirect3DDevice9* pd3dDevice, D3DXMESHCONTAINER_DERIVED* pMeshContainer );

	// unsigned int	m_NumBoneMatricesMax = 0;
	// D3DXMATRIXA16*	m_pBoneMatrices = nullptr;
	bool			m_UseSoftwareVP = false;
	METHOD			m_SkinningMethod = D3DINDEXEDHLSLVS; // Current skinning method
};

