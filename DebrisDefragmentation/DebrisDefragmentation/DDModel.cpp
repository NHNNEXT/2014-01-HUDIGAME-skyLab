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
	LPD3DXBUFFER pError = nullptr;
	LPDIRECT3DDEVICE9 pD3DDevice = DDRenderer::GetInstance()->GetDevice();
	D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
	D3DXDeclaratorFromFVF( m_MeshInfo->m_pMesh->GetFVF(), decl );
	pD3DDevice->CreateVertexDeclaration( decl, &m_pDecl );

// 	std::wstring fullpath = L".\\Shader\\";
// 	fullpath.append( filename );

//	if ( D3DXCreateEffectFromFileW( pD3DDevice, fullpath.c_str(), NULL, NULL, 0, NULL, &m_pEffect, NULL ) )
	D3DXCreateEffectFromFileW( pD3DDevice, filename.c_str(), NULL, NULL, 0, NULL, &m_pEffect, &pError );

	if ( !m_pEffect && pError )
	{
		int size = pError->GetBufferSize();
		void *ack = pError->GetBufferPointer();

		if ( ack )
		{
			wchar_t* str = new wchar_t[size];
			wsprintf( str, (const wchar_t*)ack, size );
			OutputDebugString( str );
			delete[] str;
		}
	}
	
	m_UseShader = true;
	return true;
}

void DDModel::RenderItSelf()
{
	if ( !m_MeshInfo )
		return;


	LPDIRECT3DDEVICE9 pD3DDevice = DDRenderer::GetInstance()->GetDevice();

	if ( m_UseShader )
	{
		SetupFX();
		UINT nPass;
		//pD3DDevice->SetVertexDeclaration( m_pDecl );
		//LPDIRECT3DVERTEXBUFFER9* pVB = nullptr;
		//m_MeshInfo->m_pMesh->GetVertexBuffer(pVB);
		//pD3DDevice->SetStreamSource( 0, *pVB, 0, sizeof( **pVB ) );

		//m_pEffect->SetTechnique( "RenderRimLight" );
		m_pEffect->Begin( &nPass, NULL );
		
		for ( unsigned int i = 0; i < nPass; ++i )
		{
			m_pEffect->BeginPass( i );
			for ( DWORD j = 0; j < m_MeshInfo->m_dwNumMaterials; ++j )
			{
				pD3DDevice->SetMaterial( &m_MeshInfo->m_pMeshMaterials[j] );
				pD3DDevice->SetTexture( 0, m_MeshInfo->m_pMeshTexture[j] );
				m_MeshInfo->m_pMesh->DrawSubset( j );
			}
			m_pEffect->EndPass();
		}

		m_pEffect->End();
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
