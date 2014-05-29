#include "stdafx.h"
#include "CharacterModel.h"
#include "DDRenderer.h"
#include "DDApplication.h"
#include "DDCamera.h"
#include "PlayerManager.h"


CharacterModel::CharacterModel()
{
}


CharacterModel::~CharacterModel()
{
}

void CharacterModel::UpdateItSelf( float dTime )
{
	UNREFERENCED_PARAMETER(dTime);
}

void CharacterModel::SetupFX()
{
	DDCamera* cam = GPlayerManager->GetCamera();
	D3DXVECTOR4 viewPos( cam->GetTransform().GetPosition(), 0.0f );
	D3DXMATRIXA16 wvp = cam->GetMatProj() * cam->GetMatView() * m_Matrix;
	m_pEffect->SetMatrix( "g_matWVP", &wvp );
	m_pEffect->SetMatrix( "g_matWorld", &m_Matrix );
	m_pEffect->SetVector( "g_camPos", &viewPos );
	/// 성환 : 여기작업중!! 5/30
	//m_pEffect->SetVector( "g_)
}
