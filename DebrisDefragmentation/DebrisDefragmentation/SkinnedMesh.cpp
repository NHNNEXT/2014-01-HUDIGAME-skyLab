#include "stdafx.h"
#include "SkinnedMesh.h"
#include "AllocateHierarchy.h"
#include "DDRenderer.h"
#include "PlayerManager.h"
#include "DDCamera.h"

SkinnedMesh::SkinnedMesh()
{
}


SkinnedMesh::~SkinnedMesh()
{
	ReleaseAttributeTable( m_pFrameRoot );
	delete[] m_pBoneMatrices;

	SAFE_RELEASE( m_pEffect );

	AllocateHierarchy Alloc;
	D3DXFrameDestroy( m_pFrameRoot, &Alloc );
	SAFE_RELEASE( m_pAnimController );
}

void SkinnedMesh::Init( std::wstring path )
{
	AllocateHierarchy Alloc;

	DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;

#if defined( DEBUG ) || defined( _DEBUG )
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	LPDIRECT3DDEVICE9 pD3DDevice = DDRenderer::GetInstance()->GetDevice();

	WCHAR str[MAX_PATH] = L".\\Resources\\3DModel\\SkinnedMesh.fx";

	// shader 파일 읽어서 등록
	if ( FAILED( D3DXCreateEffectFromFile( pD3DDevice, str, NULL, NULL, dwShaderFlags, NULL, &m_pEffect, NULL ) ) )
	{
		assert( false );
		return;
	}

	// shader 파일 이름 생성
	std::wstring xfilePath = L".\\Resources\\3DModel\\";
	xfilePath.append( path );

	// 메시 불러오기
	// 애니메이션 계층 구조 만들기
	if ( FAILED( D3DXLoadMeshHierarchyFromX( xfilePath.c_str(), D3DXMESH_MANAGED, pD3DDevice, &Alloc, NULL, &m_pFrameRoot, &m_pAnimController ) ) )
	{
		assert( false );
		return;
	}

	// 조심해!
	// 예제에서는 m_pBoneMatrices를 전역 변수로 사용하므로 
	// AllocateHierarchy에서 할당했으나 이제는 여기서 해준다.
	// 그런데 사이즈는 어떻게 가져오지... 아무튼 지금 애니메이션 안 나오는 문제는 여기 아님
	delete[] m_pBoneMatrices;
	m_pBoneMatrices = new D3DXMATRIXA16[64];
	if ( m_pBoneMatrices == nullptr )
	{
		assert( false );
		return;
	}

	// 본 매트릭스 생성
	if ( FAILED( SetupBoneMatrixPointers( m_pFrameRoot ) ) )
	{
		assert( false );
		return;
	}

	if ( FAILED( D3DXFrameCalculateBoundingSphere( m_pFrameRoot, &m_vObjectCenter, &m_fObjectRadius ) ) )
	{
		assert( false );
		return;
	}

	// Obtain the behavior flags
	D3DDEVICE_CREATION_PARAMETERS cp;
	pD3DDevice->GetCreationParameters( &cp );
	m_dwBehaviorFlags = cp.BehaviorFlags;
}

HRESULT SkinnedMesh::SetupBoneMatrixPointersOnMesh( LPD3DXMESHCONTAINER pMeshContainerBase )
{
	UINT iBone, cBones;
	D3DXFRAME_DERIVED* pFrame;

	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;

	// 스킨메시가 있으면
	if ( pMeshContainer->pSkinInfo != NULL )
	{
		// 본 개수를 가져와서
		cBones = pMeshContainer->pSkinInfo->GetNumBones();

		// 본 매트릭스를 저장할 공간을 할당하고
		pMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIX*[cBones];
		if ( pMeshContainer->ppBoneMatrixPtrs == NULL )
			return E_OUTOFMEMORY;

		// 매트릭스를 설정한다
		for ( iBone = 0; iBone < cBones; iBone++ )
		{
			// 해당 본의 이름을 찾아서 그걸 키로 담당 프레임을 찾나?
			pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind( m_pFrameRoot,
				pMeshContainer->pSkinInfo->GetBoneName( iBone ) );
			if ( pFrame == NULL )
				return E_FAIL;

			// 찾은 프레임에 저장된 행렬을 본에 지정한다
			pMeshContainer->ppBoneMatrixPtrs[iBone] = &pFrame->CombinedTransformationMatrix;
		}
	}

	return S_OK;
}

HRESULT SkinnedMesh::SetupBoneMatrixPointers( LPD3DXFRAME pFrame )
{
	// 메시의 본 포인터 설정
	// 해당 프레임에 있는 메시 컨테이너와 자식 형제 모두 다??

	HRESULT hr;

	if ( pFrame->pMeshContainer != NULL )
	{
		hr = SetupBoneMatrixPointersOnMesh( pFrame->pMeshContainer );
		if ( FAILED( hr ) )
			return hr;
	}

	if ( pFrame->pFrameSibling != NULL )
	{
		hr = SetupBoneMatrixPointers( pFrame->pFrameSibling );
		if ( FAILED( hr ) )
			return hr;
	}

	if ( pFrame->pFrameFirstChild != NULL )
	{
		hr = SetupBoneMatrixPointers( pFrame->pFrameFirstChild );
		if ( FAILED( hr ) )
			return hr;
	}

	return S_OK;
}

void SkinnedMesh::Update( float dt )
{
	// 조심해!!!
	// matWorld는 부모 변환행렬 넘겨주면 되려나
	D3DXMATRIXA16 matWorld; // temp
	D3DXMatrixTranslation( &matWorld, -m_vObjectCenter.x,
		-m_vObjectCenter.y,
		-m_vObjectCenter.z );

	D3DXMatrixIdentity( &matWorld );
	DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_WORLD, &matWorld );

	D3DXVECTOR3 vEye( 0, 0, -2 * m_fObjectRadius );
	D3DXVECTOR3 vAt( 0, 0, 0 );
	D3DXVECTOR3 vUp( 0, 1, 0 );
	D3DXMatrixLookAtLH( &m_MatView, &vEye, &vAt, &vUp );

	DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_VIEW, &m_MatView );

	if ( m_pAnimController != NULL )
		m_pAnimController->AdvanceTime( dt, NULL );

	UpdateFrameMatrices( m_pFrameRoot, &matWorld );
}

void SkinnedMesh::UpdateFrameMatrices( LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix )
{
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;

	if ( pParentMatrix != NULL )
		D3DXMatrixMultiply( &pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix );
	else
		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;

	if ( pFrame->pFrameSibling != NULL )
	{
		UpdateFrameMatrices( pFrame->pFrameSibling, pParentMatrix );
	}

	if ( pFrame->pFrameFirstChild != NULL )
	{
		UpdateFrameMatrices( pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix );
	}
}

// 얘는 DDModel 안으로 이동해야 할 듯
void SkinnedMesh::DrawMeshContainer( LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase )
{
	// HRESULT hr;
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
	// D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	// UINT iMaterial;
	// UINT NumBlend;
	UINT iAttrib;
	// DWORD AttribIdPrev;
	LPD3DXBONECOMBINATION pBoneComb;

	UINT iMatrixIndex;
	UINT iPaletteEntry;
	D3DXMATRIXA16 matTemp;
	D3DCAPS9 d3dCaps;

	LPDIRECT3DDEVICE9 pD3DDevice = DDRenderer::GetInstance()->GetDevice();
	pD3DDevice->GetDeviceCaps( &d3dCaps );

	// 스킨 정보있나 살펴본다
	// 스킨 형식이 아니면 안 그린다
	if ( pMeshContainer->pSkinInfo != NULL )
	{
		if ( pMeshContainer->UseSoftwareVP )
		{
			// If hw or pure hw vertex processing is forced, we can't render the
			// mesh, so just exit out.  Typical applications should create
			// a device with appropriate vertex processing capability for this
			// skinning method.
			if ( m_dwBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING )
				return;

			if ( FAILED( pD3DDevice->SetSoftwareVertexProcessing( TRUE ) ) )
			{
				assert( false );
				return;
			}
		}

		// 본 변환 행렬 배열을 가져온다
		pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>( pMeshContainer->pBoneCombinationBuf->GetBufferPointer() );

		// 카메라가 바라보는 시점 - 위치값은 반영 안 되어 있는데...
		DDCamera* camera = GPlayerManager->GetCamera();
		if ( !camera )
			return;

		D3DXMATRIX matView = camera->GetViewDirection();
		D3DXMatrixIdentity( &matView );

		// 순회하면서 변환을 적용
		for ( iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++ )
		{
			// first calculate all the world matrices
			for ( iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry )
			{
				iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
				if ( iMatrixIndex != UINT_MAX )
				{
					// 저장되어 있는 본의 변환행렬(오프셋 + 변형)을 구해서 월드좌표계에 곱해서 그려질 좌표계를 구한 뒤
					// m_pBoneMatrices에 일단 저장한다.
					D3DXMatrixMultiply( &matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex], pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex] );
					D3DXMatrixMultiply( &m_pBoneMatrices[iPaletteEntry], &matTemp, &m_MatView );
				}
			}

			// 셰이더 파일에 변환이 적용된 본의 데이터를 넘겨준다. 이때 본의 숫자도 넘겨준다.
			if ( FAILED( m_pEffect->SetMatrixArray( "mWorldMatrixArray", m_pBoneMatrices, pMeshContainer->NumPaletteEntries ) ) )
			{
				assert( false );
				return;
			}

			// 여기서부터는 셰이더에 필요한 데이터 넘겨서 실제 메시 그린 다음 렌더 방식 원래대로 돌려놓는 코드

			// Sum of all ambient and emissive contribution
			D3DXCOLOR color1( pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Ambient );
			D3DXCOLOR color2( .25, .25, .25, 1.0 );
			D3DXCOLOR ambEmm;
			D3DXColorModulate( &ambEmm, &color1, &color2 );
			ambEmm += D3DXCOLOR( pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Emissive );

			// set material color properties 
			if ( FAILED( m_pEffect->SetVector( "MaterialDiffuse",
				(D3DXVECTOR4*)&( pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Diffuse ) ) ) )
			{
				assert( false );
				return;
			}
			if ( FAILED( m_pEffect->SetVector( "MaterialAmbient", (D3DXVECTOR4*)&ambEmm ) ) )
			{
				assert( false );
				return;
			}

			// setup the material of the mesh subset - REMEMBER to use the original pre-skinning attribute id to get the correct material id
			if ( FAILED( pD3DDevice->SetTexture( 0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId] ) ) )
			{
				assert( false );
				return;
			}

			// Set CurNumBones to select the correct vertex shader for the number of bones
			if ( FAILED( m_pEffect->SetInt( "CurNumBones", pMeshContainer->NumInfl - 1 ) ) )
			{
				assert( false );
				return;
			}

			// Start the effect now all parameters have been updated
			UINT numPasses;
			if ( FAILED( m_pEffect->Begin( &numPasses, D3DXFX_DONOTSAVESTATE ) ) )
			{
				assert( false );
				return;
			}

			for ( UINT iPass = 0; iPass < numPasses; iPass++ )
			{
				if ( FAILED( m_pEffect->BeginPass( iPass ) ) )
				{
					assert( false );
					return;
				}

				// draw the subset with the current world matrix palette and material state
				if ( FAILED( pMeshContainer->MeshData.pMesh->DrawSubset( iAttrib ) ) )
				{
					assert( false );
					return;
				}

				if ( FAILED( m_pEffect->EndPass() ) )
				{
					assert( false );
					return;
				}
			}

			if ( FAILED( m_pEffect->End() ) )
			{
				assert( false );
				return;
			}

			if ( FAILED( pD3DDevice->SetVertexShader( NULL ) ) )
			{
				assert( false );
				return;
			}
		}

		// remember to reset back to hw vertex processing if software was required
		if ( pMeshContainer->UseSoftwareVP )
		{
			if ( FAILED( pD3DDevice->SetSoftwareVertexProcessing( FALSE ) ) )
			{
				assert( false );
				return;
			}
		}
	}
	else // bug out as unsupported mode
	{
		return;
	}
}

void SkinnedMesh::DrawFrame()
{
	LPD3DXMESHCONTAINER pMeshContainer;

	pMeshContainer = m_pFrameRoot->pMeshContainer;
	while ( pMeshContainer != NULL )
	{
		DrawMeshContainer( pMeshContainer, m_pFrameRoot );

		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}

	if ( m_pFrameRoot->pFrameSibling != NULL )
	{
		DrawFrame( m_pFrameRoot->pFrameSibling );
	}

	if ( m_pFrameRoot->pFrameFirstChild != NULL )
	{
		DrawFrame( m_pFrameRoot->pFrameFirstChild );
	}
}

void SkinnedMesh::DrawFrame( LPD3DXFRAME pFrame )
{
	DDCamera* camera = GPlayerManager->GetCamera();
	if ( !camera )
		return;

	D3DXMATRIXA16 matProj = camera->GetMatProj();

	// Set the projection matrix for the vertex shader based skinning method
	if ( FAILED( m_pEffect->SetMatrix( "mViewProj", &matProj ) ) )
	{
		assert( false );
		return;
	}

	// Set Light for vertex shader
	// 조심해!! 
	// 전역 라이트 속성 가져올 것
	D3DXVECTOR4 vLightDir( 0.0f, 1.0f, -1.0f, 0.0f );
	D3DXVec4Normalize( &vLightDir, &vLightDir );
	if ( FAILED( DDRenderer::GetInstance()->GetDevice()->SetVertexShaderConstantF( 1, (float*)&vLightDir, 1 ) ) )
	{
		assert( false );
		return;
	}

	if ( FAILED( m_pEffect->SetVector( "lhtDir", &vLightDir ) ) )
	{
		assert( false );
		return;
	}

	LPD3DXMESHCONTAINER pMeshContainer;

	pMeshContainer = pFrame->pMeshContainer;
	while ( pMeshContainer != NULL )
	{
		DrawMeshContainer( pMeshContainer, pFrame );

		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}

	if ( pFrame->pFrameSibling != NULL )
	{
		DrawFrame( pFrame->pFrameSibling );
	}

	if ( pFrame->pFrameFirstChild != NULL )
	{
		DrawFrame( pFrame->pFrameFirstChild );
	}
}

void SkinnedMesh::ReleaseAttributeTable( LPD3DXFRAME pFrameBase )
{
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	D3DXMESHCONTAINER_DERIVED* pMeshContainer;

	pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrame->pMeshContainer;

	while ( pMeshContainer != NULL )
	{
		delete[] pMeshContainer->pAttributeTable;

		pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainer->pNextMeshContainer;
	}

	if ( pFrame->pFrameSibling != NULL )
	{
		ReleaseAttributeTable( pFrame->pFrameSibling );
	}

	if ( pFrame->pFrameFirstChild != NULL )
	{
		ReleaseAttributeTable( pFrame->pFrameFirstChild );
	}
}