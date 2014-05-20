#include "stdafx.h"
#include "ModelPool.h"


ModelPool::ModelPool()
{
}


ModelPool::~ModelPool()
{
	ClearModelPool();
}


bool ModelPool::InitModel( ModelType modelType, std::wstring path )
{
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

	// texture �ҷ����� �κ�, bmp���� ��θ� ���� ���͸��� ������ŭ �ҷ���
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
		//������ ���� �ʴٸ� �޽��� �����ϰ� D3DFVF_NORMAL�� �߰��Ѵ�.
		ID3DXMesh* pTempMesh = 0;
		mi->m_pMesh->CloneMeshFVF(
			D3DXMESH_MANAGED,
			mi->m_pMesh->GetFVF() | D3DFVF_NORMAL,  //�̰��� �߰�
			DDRenderer::GetInstance()->GetDevice(),
			&pTempMesh );

		// ������ ����Ѵ�.
		if ( FAILED( D3DXComputeNormals( pTempMesh, 0 ) ) )
		{
			return false;
		}

		mi->m_pMesh->Release(); // �����޽��� �����Ѵ�
		mi->m_pMesh = pTempMesh; // �����޽��� ������ ���� �޽��� �����Ѵ�.
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
		return findIter->second;
	}
	return nullptr;
}

void ModelPool::ClearModelPool()
{
	// model���� ��ȸ�鼭 mesh, texture, material���� resource�� ����	
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