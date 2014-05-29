#include "stdafx.h"
#include "DDModel.h"
#include "DDRenderer.h"
#include "DDApplication.h"

DDModel::DDModel()
{
}

DDModel::~DDModel()
{

}

bool DDModel::InitFX( std::wstring filename )
{
	LPDIRECT3DDEVICE9 pD3DDevice = DDRenderer::GetInstance()->GetDevice();
	D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
	D3DXDeclaratorFromFVF( m_MeshInfo->m_pMesh->GetFVF(), decl );
	pD3DDevice->CreateVertexDeclaration( decl, &m_pDecl );

// 	std::wstring fullpath = L".\\Shader\\";
// 	fullpath.append( filename );

//	if ( D3DXCreateEffectFromFileW( pD3DDevice, fullpath.c_str(), NULL, NULL, 0, NULL, &m_pEffect, NULL ) )
	if ( D3DXCreateEffectFromFileW( pD3DDevice, filename.c_str(), NULL, NULL, 0, NULL, &m_pEffect, NULL ) )
	{
		return false;
	}
	m_UseShader = true;
	return true;
}

void DDModel::RenderItSelf()
{
	if ( !m_MeshInfo )
		return;

	SetupFX();

	LPDIRECT3DDEVICE9 pD3DDevice = DDRenderer::GetInstance()->GetDevice();

	if ( m_UseShader )
	{

	}
	else
	{
		for ( DWORD i = 0; i < m_MeshInfo->m_dwNumMaterials; ++i )
		{
			pD3DDevice->SetMaterial( &m_MeshInfo->m_pMeshMaterials[i] );
			pD3DDevice->SetTexture( 0, m_MeshInfo->m_pMeshTexture[i] );
			m_MeshInfo->m_pMesh->DrawSubset( i );
		}
	}
	
}
