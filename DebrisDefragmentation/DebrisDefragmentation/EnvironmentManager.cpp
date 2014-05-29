#include "stdafx.h"
#include "EnvironmentManager.h"
#include "DDLight.h"

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
