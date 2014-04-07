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
	DDModel* pInstance = new DDModel(filePath);
	return pInstance;	
}

bool DDModel::initModel( wchar_t* path )
{
	LPD3DXBUFFER pD3DXMtrlBuffer;	

	std::wstring xfilePath = L".\\Resources\\3DModel\\";
	xfilePath.append(path);
	
	//wcscat_s( resourcePath, MAX_PATH , path );

	HRESULT hr;
	hr = D3DXLoadMeshFromX( xfilePath.c_str(), D3DXMESH_SYSTEMMEM, m_pD3DDevice, NULL, &pD3DXMtrlBuffer, NULL, &m_dwNumMaterials, &m_pMesh );

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
 			std::string bmpPath = ".\\Resources\\3DModel\\";
// 			CHAR strTexture[MAX_PATH];
// 			strcpy_s( strTexture, MAX_PATH, strPrefix );
			bmpPath.append(d3dxMaterials[i].pTextureFilename );

			if ( FAILED( D3DXCreateTextureFromFileA( m_pD3DDevice, bmpPath.c_str(), &m_pMeshTexture[i] ) ) )
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
		//가지고 있지 않다면 메쉬를 복제하고 D3DFVF_NORMAL을 추가한다.
		ID3DXMesh* pTempMesh = 0;
		m_pMesh->CloneMeshFVF(
			D3DXMESH_MANAGED,
			m_pMesh->GetFVF() | D3DFVF_NORMAL,  //이곳에 추가
			m_pD3DDevice,
			&pTempMesh );

		// 법선을 계산한다.
		if ( FAILED( D3DXComputeNormals( pTempMesh, 0 ) ) )
		{
			return false;
		}

		m_pMesh->Release(); // 기존메쉬를 제거한다
		m_pMesh = pTempMesh; // 기존메쉬를 법선이 계산된 메쉬로 지정한다.
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
