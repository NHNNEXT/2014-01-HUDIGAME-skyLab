#pragma once

#include "d3dx9.h"

// 조심해!!
// 일단 상속말고 직접 구현하는 걸로 만들고 나중에 수정

class SkinnedMesh
{
public:
	SkinnedMesh();
	~SkinnedMesh();

	void Init( std::wstring path );
	void Update( float dt );
	
	void DrawFrame();
	void DrawFrame( LPD3DXFRAME pFrame );

private:
	HRESULT SkinnedMesh::SetupBoneMatrixPointersOnMesh( LPD3DXMESHCONTAINER pMeshContainerBase );
	HRESULT SkinnedMesh::SetupBoneMatrixPointers( LPD3DXFRAME pFrame ); // 호출할 때 인자는 기본적으로 m_pFrameRoot를 넣으면 된다
	void DrawMeshContainer( LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase );
	void ReleaseAttributeTable( LPD3DXFRAME pFrameBase );

	void UpdateFrameMatrices( LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix );

	ID3DXEffect*				m_pEffect = NULL;       // D3DX effect interface
	LPD3DXFRAME					m_pFrameRoot = NULL;	// 뼈대 - fps의 프레임이 아님 스켈레톤!
	ID3DXAnimationController*	m_pAnimController = NULL;
	D3DXVECTOR3                 m_vObjectCenter;        // Center of bounding sphere of object
	FLOAT                       m_fObjectRadius;        // Radius of bounding sphere of object
	DWORD                       m_dwBehaviorFlags;      // Behavior flags of the 3D device

	// 그려지는 본 숫자만큼 메모리를 할당해서 버퍼로 계속 유지해야 한다
	// 그릴 때마다 생성해서 쓰면 너무 비용이 비싸다
	D3DXMATRIXA16*	m_pBoneMatrices = nullptr;

	// 이건 DDModel안에 밀어 넣으면서 부모 좌표계랑 본인 좌표계 곱해서 구해서 사용 - 사실상 m_Matrix
	D3DXMATRIXA16 m_MatView; // temp
};

