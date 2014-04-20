#pragma once
#include "DDModel.h"
class Debris :
	public DDModel
{
public:
	Debris();
	Debris( std::wstring modelPath );
	virtual ~Debris();

	//static Debris* Create( wchar_t* modelPath );
	CREATE_FUNC_WSTRING( Debris, modelpath );
	
private:
	virtual void UpdateItSelf( float dTime );

	float tmpTimeCounter;
};
