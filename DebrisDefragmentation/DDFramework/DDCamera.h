#pragma once
#include "DDObject.h"
class DDCamera : public DDObject
{
public:
	DDCamera();
	virtual ~DDCamera();
	
	static DDCamera* Create();

	virtual void Render();
	virtual void Update( float dTime );
};

