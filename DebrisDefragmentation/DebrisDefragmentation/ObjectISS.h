#pragma once
#include "DDModel.h"
class ObjectISS :
	public DDModel
{
public:
	ObjectISS();
	ObjectISS( std::wstring modelPath );
	virtual ~ObjectISS();

	CREATE_OBJECT_WSTRING( ObjectISS, modelpath );

private:
	virtual void UpdateItSelf( float dTime );

	float tmpTimeCounter;
};
