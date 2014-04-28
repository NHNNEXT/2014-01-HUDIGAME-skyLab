#pragma once
#include "DDModel.h"
class ISS :
	public DDModel
{
public:
	ISS();
	ISS( std::wstring modelPath );
	virtual ~ISS();

	CREATE_OBJECT_WSTRING( ISS, modelpath );

private:
	virtual void UpdateItSelf( float dTime );

	float tmpTimeCounter;
};
