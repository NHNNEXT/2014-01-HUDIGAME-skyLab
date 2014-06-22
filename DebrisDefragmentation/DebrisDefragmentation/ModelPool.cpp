#include "stdafx.h"
#include "ModelPool.h"


ModelPool::ModelPool()
{
}


ModelPool::~ModelPool()
{
	ClearModelPool();
}


bool ModelPool::InitModel( ModelType modelType, std::wstring path, bool isAnimation )
{
	if ( isAnimation )
	{
		// 애니메이션 모델을 만든다.
		SkinnedMesh* newSkinnedMesh = new SkinnedMesh();
		if ( newSkinnedMesh == nullptr )
			return false;

		if ( !newSkinnedMesh->Init( path.c_str() ) )
			return false;

		m_AnimationObjectMap.insert( std::pair<ModelType, SkinnedMesh*>( modelType, newSkinnedMesh ) );
		
		return true;
	}

	MeshInfo* mi = new MeshInfo();
	LPD3DXBUFFER		pD3DXMtrlBuffer;
	LPDIRECT3DDEVICE9	pD3DDevice = DDRenderer::GetInstance()->GetDevice();

	std::wstring xfilePath = L".\\Resources\\3DModel\\";
	xfilePath.append( path );

	if ( FAILED( D3DXLoadMeshFromX( xfilePath.c_str(), D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &pD3DXMtrlBuffer, NULL, &mi->m_dwNumMaterials, &mi->m_pMesh ) ) )
	{
		// x file loading error
		assert( 0 );
		printf( "No Model\n" );
		return false;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	mi->m_pMeshMaterials = new D3DMATERIAL9[mi->m_dwNumMaterials];
	if ( mi->m_pMeshMaterials == NULL )
	{
		// out of memory
		assert( 0 );
		return false;
	}

	mi->m_pMeshTexture = new LPDIRECT3DTEXTURE9[mi->m_dwNumMaterials];
	if ( mi->m_pMeshTexture == NULL )
	{
		// out of memory
		assert( 0 );
		return false;
	}

	// texture 불러오는 부분, bmp파일 경로를 통해 매터리얼 개수만큼 불러옴
	for ( DWORD i = 0; i < mi->m_dwNumMaterials; i++ )
	{
		mi->m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		mi->m_pMeshMaterials[i].Ambient = mi->m_pMeshMaterials[i].Diffuse;

		mi->m_pMeshTexture[i] = NULL;
		if ( d3dxMaterials[i].pTextureFilename != NULL && lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
		{
			std::string bmpPath = ".\\Resources\\3DModel\\";
			bmpPath.append( d3dxMaterials[i].pTextureFilename );

			if ( FAILED( D3DXCreateTextureFromFileA( pD3DDevice, bmpPath.c_str(), &mi->m_pMeshTexture[i] ) ) )
			{
				//MessageBox( NULL, L"no texture map", L"Meshes.exe", MB_OK );
				// no texture error
				assert( 0 );
				return false;
			}
		}
	}

	pD3DXMtrlBuffer->Release();

	if ( !SetNormalVector( mi ) )
	{
		// failed compute normal vector 
		assert( 0 );
		return false;
	}

	AddModel( modelType, mi );

	return true;
}


bool ModelPool::SetNormalVector( MeshInfo* mi )
{
	if ( !( mi->m_pMesh->GetFVF() & D3DFVF_NORMAL ) )
	{
		//가지고 있지 않다면 메쉬를 복제하고 D3DFVF_NORMAL을 추가한다.
		ID3DXMesh* pTempMesh = 0;
		if ( FAILED( mi->m_pMesh->CloneMeshFVF(
			D3DXMESH_MANAGED,
			mi->m_pMesh->GetFVF() | D3DFVF_NORMAL,  //이곳에 추가
			DDRenderer::GetInstance()->GetDevice(),
			&pTempMesh ) ) )
		{
			return false;
		}

		// 법선을 계산한다.
		if ( FAILED( D3DXComputeNormals( pTempMesh, 0 ) ) )
		{
			return false;
		}

		mi->m_pMesh->Release(); // 기존메쉬를 제거한다
		mi->m_pMesh = pTempMesh; // 기존메쉬를 법선이 계산된 메쉬로 지정한다.
	}

	return true;
}


void ModelPool::AddModel( ModelType mt, MeshInfo* mi )
{	
	m_ObjectMap.insert( std::pair<ModelType, MeshInfo*>( mt, mi) );
}

MeshInfo* ModelPool::GetModel( ModelType modelName )
{	
	auto findIter = m_ObjectMap.find( modelName );
	if ( findIter != m_ObjectMap.end() )
	{		
// 		MeshInfo* tmpMesh = new MeshInfo( *findIter->second );		
// 		return tmpMesh;
		return findIter->second;
	}
	return nullptr;
}

SkinnedMesh* ModelPool::GetAnimationModel( ModelType modelName )
{
	auto findIter = m_AnimationObjectMap.find( modelName );
	if ( findIter != m_AnimationObjectMap.end() )
	{
		return findIter->second;
	}
	return nullptr;
}

void ModelPool::ClearModelPool()
{
	// model별로 순회면서 mesh, texture, material등의 resource를 해제	
	for ( auto eachModel : m_ObjectMap )
	{
		if ( !Cleanup( eachModel.second ) )
		{ 
			// cleanup error
			printf_s( "Model mesh clean up failed\n" );
			assert( 0 );			
		}
		delete eachModel.second;
	}
	m_ObjectMap.clear();

	// animation 객체들 관리
	for ( auto eachModel : m_AnimationObjectMap )
	{
		delete eachModel.second;
	}
	m_AnimationObjectMap.clear();
}

bool ModelPool::Cleanup( MeshInfo* mi )
{
	// texture release
	if ( mi->m_pMeshTexture )
	{
		for ( DWORD i = 0; i < mi->m_dwNumMaterials; ++i )
		{
			if ( mi->m_pMeshTexture[i] )
			{
				mi->m_pMeshTexture[i]->Release();
			}
		}
		delete[] mi->m_pMeshTexture;
		mi->m_pMeshTexture = nullptr;
	}

	// mesh release
	if ( mi->m_pMeshMaterials != NULL )
	{
		delete[] mi->m_pMeshMaterials;
		mi->m_pMeshMaterials = nullptr;
	}

	if ( mi->m_pMesh != nullptr )
	{
		mi->m_pMesh->Release();
		mi->m_pMesh = nullptr;
	}

	return true;
}