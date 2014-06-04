#pragma once

#include "Environment.h"
#include "DDUI.h"

class DDScene;

class DDUIModule
{
public:
	DDUIModule();
	virtual ~DDUIModule();

	bool Init( DDScene* scene );
	
	virtual void Update( float dt ) = 0;

protected:
	virtual bool GenerateUI() = 0;
	void RegisterUI( DDScene* scene );
	void MakeUIComponent( ClientUITag tag );

	std::map<ClientUITag, DDUI*> m_UIComponentList;
};

