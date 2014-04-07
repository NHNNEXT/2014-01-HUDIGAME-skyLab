#pragma once
#include "DDObject.h"
class DDLight :
	public DDObject
{
public:
	DDLight();
	virtual ~DDLight();

	static DDLight* Create();

	virtual void Render();
	virtual void Update( float dTime );
};

