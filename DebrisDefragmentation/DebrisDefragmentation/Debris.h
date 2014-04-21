#pragma once
#include "DDModel.h"
class Debris :
	public DDModel
{
public:
	Debris();
	Debris( std::wstring modelPath );
	virtual ~Debris();

	CREATE_OBJECT_WSTRING( Debris, modelpath );
	
private:
	virtual void UpdateItSelf( float dTime );

	float tmpTimeCounter;
};
