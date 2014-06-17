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
	int			PlayParticleEffect( EffectType effectType, D3DXVECTOR3 origin = ZERO_VECTOR3 );
//	bool		IsPlaying( int effectId, EffectType effectType );

private:
	std::array<Firework*, PARTICLE_EFFECT_BUFFER> m_ExplosionEffectList;
	std::array<Firework*, PARTICLE_EFFECT_BUFFER> m_HealingEffectList;
	Snow* m_DebrisStrike = nullptr;
	int m_CurrentFireworkEffectNumber = 0;
	std::map<ClientLightTag, DDLight*> m_LightMap;
};

extern std::shared_ptr<EnvironmentManager> GEnvironmentManager;
