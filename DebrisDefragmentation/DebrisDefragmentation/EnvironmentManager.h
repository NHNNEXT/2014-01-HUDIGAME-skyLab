#pragma once
#include "DDConfig.h"
#include "DDMacro.h"
#include "Environment.h"

class DDLight;

class EnvironmentManager
{
public:
	EnvironmentManager();
	~EnvironmentManager();

	CREATE_FUNC( EnvironmentManager );

	void AddLight( ClientLightTag lightName, DDLight* light ) { m_LightMap[lightName] = light; }
	DDLight* GetLight( ClientLightTag lightName );

private:

	std::map<ClientLightTag, DDLight*> m_LightMap;
};

extern std::shared_ptr<EnvironmentManager> GEnvironmentManager;
