#pragma once
#include "DDModel.h"
class Debris :
	public DDModel
{
public:
	Debris();
	virtual ~Debris();

	CREATE_FUNC( Debris );

	virtual void Render();
	virtual void Update( float dTime );
};

