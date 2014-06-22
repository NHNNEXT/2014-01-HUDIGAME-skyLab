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
	if ( m_IncludeAnimation )
	{
		DrawAnimationMesh();
	}
	else
	{
		DrawMesh();
	}
}

void DDModel::DrawMesh()
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

void DDModel::DrawAnimationMesh()
{
	if ( !m_SkinnedMeshInfo )
		return;
	
	m_AnimationPlayTime -= m_Dt;

	if ( m_Dt < 0 )
	{
		switch ( m_CurrentCharacterState )
		{
		case CharacterAnimState::REACT:
			m_AnimationPlayTime = ANIM_TIME_REACT;
			break;
		default:
			m_CurrentCharacterState = CharacterAnimState::IDLE;
			m_AnimationPlayTime = ANIM_TIME_IDLE;
			break;
		}
	}
	m_SkinnedMeshInfo->SetAnimationTrack( static_cast<int>( m_CurrentCharacterState ) );

	// 그리기 직전에 업데이트 시켜주면 그리는 동안에는 내 정보 기반으로 그리지 않을까?!
	m_SkinnedMeshInfo->Update( m_Dt, &m_Matrix );
	m_Dt = 0.0f;

	m_SkinnedMeshInfo->DrawFrame();
}

void DDModel::SetModelMesh( MeshInfo* mi ) 
{ 
	m_SkinnedMeshInfo = nullptr;

	m_MeshInfo = mi; 
	m_IncludeAnimation = false;
}

void DDModel::SetModelSkinnedMesh( SkinnedMesh* mi ) 
{ 
	m_MeshInfo = nullptr;

	m_SkinnedMeshInfo = mi; 
	m_IncludeAnimation = true;

	m_CurrentCharacterState = CharacterAnimState::IDLE;
	m_AnimationPlayTime = ANIM_TIME_IDLE;
}

void DDModel::SetCharacterAnimationState( CharacterAnimState state )
{
	m_CurrentCharacterState = state;

	switch ( m_CurrentCharacterState )
	{
	case CharacterAnimState::ATTACK:
		m_AnimationPlayTime = ANIM_TIME_ATTACK;
		break;
	case CharacterAnimState::DEAD:
		m_AnimationPlayTime = ANIM_TIME_DEAD;
		break;
	case CharacterAnimState::FIRE:
		m_AnimationPlayTime = ANIM_TIME_FIRE;
		break;
	case CharacterAnimState::IDLE:
		m_AnimationPlayTime = ANIM_TIME_IDLE;
		break;
	case CharacterAnimState::REACT:
		m_AnimationPlayTime = ANIM_TIME_REACT;
		break;
	default:
		break;
	}
}