#pragma once
#include "DDModel.h"
class Debris :
	public DDModel
{
public:
	Debris();
	Debris( wchar_t* modelPath );
	virtual ~Debris();

	static Debris* Create( wchar_t* modelPath );
	
private:
	virtual void UpdateItSelf( float dTime );

	float tmpTimeCounter;
};
