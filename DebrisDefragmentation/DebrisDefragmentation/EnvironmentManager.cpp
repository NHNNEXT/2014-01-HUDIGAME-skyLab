#include "stdafx.h"
#include "EnvironmentManager.h"
#include "DDLight.h"
#include "GameOption.h"
#include "SceneManager.h"
#include "PlayScene.h"

extern std::shared_ptr<EnvironmentManager> GEnvironmentManager = nullptr;

EnvironmentManager::EnvironmentManager()
{
}


EnvironmentManager::~EnvironmentManager()
{
}

DDLight* EnvironmentManager::GetLight( ClientLightTag lightName )
{
	if ( m_LightMap.find( lightName ) != m_LightMap.end() ) 
		return m_LightMap[lightName];
	return nullptr;
}

void EnvironmentManager::InitParticleEffects()
{
	D3DXVECTOR3 origin( TEMP_ORIGIN );
	
	for ( int i = 0; i < PARTICLE_EFFECT_BUFFER; ++i )
	{
		Firework* Exp = Firework::Create();
		Exp->SetParticles( &origin, NUMBER_OF_PARTICLES );
		Exp->init( DDRenderer::GetInstance()->GetDevice(), L"flare.bmp" );
		m_FireworkEffectList[i] = Exp;
		GSceneManager->GetScene()->AddChild( Exp );		
	}
	
}
