#include "DDConfig.h"
#include "DDModel.h"
#include "DDRenderer.h"
#include "DDApplication.h"

DDModel::DDModel()
{
}

DDModel::DDModel( wchar_t* path )
{
	//m_pD3DDevice = DDRenderer::GetInstance()->GetDevice();
	initModel( path );
	SetNormalVector();
}

DDModel::DDModel( wchar_t* path, LPDIRECT3DDEVICE9 device )
{
	//m_pD3DDevice = device;
	initModel( path, device );
	SetNormalVector();
}

DDModel::~DDModel()
{
	Cleanup();
}

DDModel* DDModel::Create( wchar_t* filePath )
{
	return Create( filePath, DDRenderer::GetInstance()->GetDevice() );
}

DDModel* DDModel::Create( wchar_t* filePath, LPDIRECT3DDEVICE9 device )
{
	DDModel* pInstance = new DDModel( filePath, device );
	return pInstance;
}

bool DDModel::initModel( wchar_t* path, LPDIRECT3DDEVICE9 device )
{
	LPD3DXBUFFER		pD3DXMtrlBuffer;

	std::wstring xfilePath = L".\\Resources\\3DModel\\";
	xfilePath.append( path );

	if ( FAILED( D3DXLoadMeshFromX( xfilePath.c_str(), D3DXMESH_SYSTEMMEM, device, NULL, &pD3DXMtrlBuffer, NULL, &m_dwNumMaterials, &m_pMesh ) ) )
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

	// texture �ҷ����� �κ�, bmp���� ��θ� ���� ���͸��� ������ŭ �ҷ���
	for ( DWORD i = 0; i < m_dwNumMaterials; i++ )
	{
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;

		m_pMeshTexture[i] = NULL;
		if ( d3dxMaterials[i].pTextureFilename != NULL && lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
		{
			std::string bmpPath = ".\\Resources\\3DModel\\";
			bmpPath.append( d3dxMaterials[i].pTextureFilename );

			if ( FAILED( D3DXCreateTextureFromFileA( device, bmpPath.c_str(), &m_pMeshTexture[i] ) ) )
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

bool DDModel::initModel( wchar_t* path )
{
	return initModel( path, DDRenderer::GetInstance()->GetDevice() );
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
			DDRenderer::GetInstance()->GetDevice(),
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
	if ( m_pMesh != nullptr )
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	return true;
}


void DDModel::RenderItSelf()
{
	LPDIRECT3DDEVICE9 pD3DDevice = DDRenderer::GetInstance()->GetDevice();
	for ( DWORD i = 0; i < m_dwNumMaterials; ++i )
	{
		pD3DDevice->SetMaterial( &m_pMeshMaterials[i] );
		pD3DDevice->SetTexture( 0, m_pMeshTexture[i] );

		m_pMesh->DrawSubset( i );
	}
}
