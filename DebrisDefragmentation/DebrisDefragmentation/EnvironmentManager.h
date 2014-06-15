#pragma once
#include "DDConfig.h"
#include "DDMacro.h"
#include "Environment.h"
#include "ParticleSystem.h"
#include "GameOption.h"

class DDLight;

class EnvironmentManager
{
public:
	EnvironmentManager();
	~EnvironmentManager();

	CREATE_FUNC( EnvironmentManager );

	void		AddLight( ClientLightTag lightName, DDLight* light ) { m_LightMap[lightName] = light; }
	DDLight*	GetLight( ClientLightTag lightName );
	void		InitParticleEffects();	
	void		PlayFireworkEffect(D3DXVECTOR3 origin) { m_FireworkEffectList[( m_CurrentFireworkEffectNumber++ ) % PARTICLE_EFFECT_BUFFER]->PlayEffect(origin); }

private:
	std::array<Firework*, PARTICLE_EFFECT_BUFFER> m_FireworkEffectList;
	std::array<Firework*, PARTICLE_EFFECT_BUFFER> m_HealingEffectList;
	int m_CurrentFireworkEffectNumber = 0;
	std::map<ClientLightTag, DDLight*> m_LightMap;
};

extern std::shared_ptr<EnvironmentManager> GEnvironmentManager;
