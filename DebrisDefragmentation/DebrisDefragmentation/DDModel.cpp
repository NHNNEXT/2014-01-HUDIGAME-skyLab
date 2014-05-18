#include "stdafx.h"
#include "DDModel.h"
#include "DDRenderer.h"
#include "DDApplication.h"


DDModel::DDModel()
{
}
// 
// DDModel::DDModel( std::wstring path )
// {
// 	
// }

DDModel::~DDModel()
{

}

void DDModel::RenderItSelf()
{
	if ( !m_MeshInfo )
		return;

	LPDIRECT3DDEVICE9 pD3DDevice = DDRenderer::GetInstance()->GetDevice();
	for ( DWORD i = 0; i < m_MeshInfo->m_dwNumMaterials; ++i )
	{
		pD3DDevice->SetMaterial( &m_MeshInfo->m_pMeshMaterials[i] );
		pD3DDevice->SetTexture( 0, m_MeshInfo->m_pMeshTexture[i] );
		m_MeshInfo->m_pMesh->DrawSubset( i );
	}
}
