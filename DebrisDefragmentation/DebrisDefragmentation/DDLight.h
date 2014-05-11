#pragma once
#include "ClientObject.h"
class DDLight :
	public ClientObject
{
public:
	DDLight();
	virtual ~DDLight();

	CREATE_OBJECT( DDLight );
	//static DDLight* Create();

protected:
	virtual void RenderItSelf();
};

