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

	void Update( float dTime );
	void UpdateItSelf( float dTime );

private:
	float tmpTimeCounter;
};
