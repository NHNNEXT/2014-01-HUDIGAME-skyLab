#include "stdafx.h"
#include "EnvironmentManager.h"
#include "DDLight.h"
#include "GameOption.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include "DDMath.h"

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
	// init firework effect
	for ( int i = 0; i < PARTICLE_EFFECT_BUFFER; ++i )
	{
		Firework* Exp = Firework::Create();		
		Exp->SetParticles( TEMP_ORIGIN, EXPLOSION_COLOR_RANGE, EXPLOSION_DIR_MIN, EXPLOSION_DIR_MAX, EXPLOSION_LIFETIME, NUMBER_OF_PARTICLES, EXPLOSION_PARTICLE_VELOCITY );
		Exp->init( DDRenderer::GetInstance()->GetDevice(), L"flare.bmp" );
		m_ExplosionEffectList[i] = Exp;
		GSceneManager->GetScene()->AddChild( Exp );		

		Firework* Heal = Firework::Create();
		Heal->SetParticles( TEMP_ORIGIN, HEALING_COLOR_RANGE, HEALING_DIR_MIN, HEALING_DIR_MAX, HEALING_LIFETIME, NUMBER_OF_PARTICLES, HEALING_PARTICLE_VELOCITY);
		Heal->init( DDRenderer::GetInstance()->GetDevice(), L"green_cross.png" );
		m_HealingEffectList[i] = Heal;
		GSceneManager->GetScene()->AddChild( Heal );
	}

	m_DebrisStrike = Snow::Create();
	m_DebrisStrike->SetParticles( TEMP_ORIGIN, DS_COLOR_RANGE, DS_DIR_MAX, DS_ORIGIN_MIN, DS_ORIGIN_MAX, DS_LIFETIME, NUMBER_OF_DS_PARTICLES, DS_PARTICLE_VELOCITY );
	m_DebrisStrike->init( DDRenderer::GetInstance()->GetDevice(), L"snowflake.dds" );
	GSceneManager->GetScene()->AddChild( m_DebrisStrike );
	
}

int EnvironmentManager::PlayFireworkEffect( EffectType effectType, D3DXVECTOR3 origin, D3DXVECTOR3 directionMin /*= EXPLOSION_DIR_MIN*/, D3DXVECTOR3 directionMax /*= EXPLOSION_DIR_MIN */)
{
	switch ( effectType )
	{
		case EffectType::EXPLOSION:
			m_ExplosionEffectList[m_CurrentFireworkEffectNumber % PARTICLE_EFFECT_BUFFER]->PlayEffect( origin , directionMin, directionMax); 
			return m_CurrentFireworkEffectNumber++;			
		case EffectType::HEALING:
			m_HealingEffectList[m_CurrentFireworkEffectNumber % PARTICLE_EFFECT_BUFFER]->PlayEffect( origin, directionMin, directionMax );
			return m_CurrentFireworkEffectNumber++;			
		default:
			break;
	}
	
	return -1;
}

void EnvironmentManager::PlaySnowEffect( D3DXVECTOR3 direction, float remainTime )
{
	m_DebrisStrike->PlayEffect(direction, remainTime);
}

// 
// bool EnvironmentManager::IsPlaying( int effectId, EffectType effectType )
// {
// 	switch ( effectType )
// 	{
// 		case EffectType::EXPLOSION:
// 			return m_ExplosionEffectList[effectId]->isDead();			
// 		case EffectType::HEALING:
// 			return m_HealingEffectList[effectId]->isDead();
// 			break;
// 		default:
// 			break;
// 	}
// }
