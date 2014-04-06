#include "DDConfig.h"
#include "DDModel.h"
#include "DDRenderer.h"

DDModel::DDModel():
m_pMesh(NULL),
m_pMeshMaterials(NULL),
m_pMeshTexture(NULL),
m_dwNumMaterials(0L)
{
}

DDModel::DDModel( wchar_t* path )
{
	m_pD3DDevice = DDRenderer::GetInstance()->GetDevice();
	initModel( path );
	SetNormalVector();
}



DDModel::~DDModel()
{
	Cleanup();
}

DDModel* DDModel::Create( wchar_t* filePath )
{
	DDModel* pInstance = new DDModel;
	return pInstance;	
}

bool DDModel::initModel( wchar_t* path )
{
	LPD3DXBUFFER pD3DXMtrlBuffer;	

	wchar_t* resourcePath = L"Resources//3DModel";
	wcscat_s( resourcePath, MAX_PATH , path );

	HRESULT hr;
	hr = D3DXLoadMeshFromX( resourcePath, D3DXMESH_SYSTEMMEM, m_pD3DDevice, NULL, &pD3DXMtrlBuffer, NULL, &m_dwNumMaterials, &m_pMesh );

	if ( FAILED( hr ) )
	{
		// x file loading error
		return false;
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	if ( m_pMeshMaterials == NULL )
	{
		// out of memory
		return false;
	}

	m_pMeshTexture = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];
	if ( m_pMeshTexture == NULL )
	{
		// out of memory
		return false;
	}

	for ( DWORD i = 0; i < m_dwNumMaterials; i++ )
	{
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

		m_pMeshTexture[i] = NULL;
		if ( d3dxMaterials[i].pTextureFilename != NULL && lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
		{
			const CHAR* strPrefix = "..\\";
			CHAR strTexture[MAX_PATH];
			strcpy_s( strTexture, MAX_PATH, strPrefix );
			strcat_s( strTexture, MAX_PATH, d3dxMaterials[i].pTextureFilename );

			if ( FAILED( D3DXCreateTextureFromFileA( m_pD3DDevice, strTexture, &m_pMeshTexture[i] ) ) )
			{
				/*MessageBox( NULL, L"no texture map", L"Meshes.exe", MB_OK );*/
				// no texture error
				return false;
			}
		}
	}

	pD3DXMtrlBuffer->Release();

	return true;
}


bool DDModel::SetNormalVector()
{
	if ( !( m_pMesh->GetFVF() & D3DFVF_NORMAL ) )
	{
		//������ ���� �ʴٸ� �޽��� �����ϰ� D3DFVF_NORMAL�� �߰��Ѵ�.
		ID3DXMesh* pTempMesh = 0;
		m_pMesh->CloneMeshFVF(
			D3DXMESH_MANAGED,
			m_pMesh->GetFVF() | D3DFVF_NORMAL,  //�̰��� �߰�
			m_pD3DDevice,
			&pTempMesh );

		// ������ ����Ѵ�.
		if ( FAILED( D3DXComputeNormals( pTempMesh, 0 ) ) )
		{
			return false;
		}

		m_pMesh->Release(); // �����޽��� �����Ѵ�
		m_pMesh = pTempMesh; // �����޽��� ������ ���� �޽��� �����Ѵ�.
	}

	return true;
}

bool DDModel::Cleanup()
{
	// texture release
	if ( m_pMeshTexture )
	{
		for ( DWORD i = 0; i < m_dwNumMaterials; ++i )
		{
			if ( m_pMeshTexture[i] )
			{
				m_pMeshTexture[i]->Release();
			}
		}
		delete[] m_pMeshTexture;
		m_pMeshTexture = nullptr;
	}

	// mesh release
	if ( m_pMeshMaterials != NULL )
	{
		delete[] m_pMeshMaterials;
		m_pMeshMaterials = nullptr;
	}

	return true;
}

void DDModel::Render()
{
	DDObject::Render();

	for ( DWORD i = 0; i < m_dwNumMaterials; ++i )
	{
		m_pD3DDevice->SetMaterial( &m_pMeshMaterials[i] );
		m_pD3DDevice->SetTexture( 0, m_pMeshTexture[i] );

		m_pMesh->DrawSubset( i );
	}
}

void DDModel::Update( float dTime )
{
	DDObject::Update( dTime );
}
