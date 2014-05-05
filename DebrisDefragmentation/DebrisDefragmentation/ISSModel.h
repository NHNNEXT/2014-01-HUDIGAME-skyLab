#pragma once
#include "DDModel.h"
class ISSModel :
	public DDModel
{
public:
	ISSModel( );
	ISSModel( std::wstring modelPath );
	virtual ~ISSModel( );

	CREATE_OBJECT_WSTRING( ISSModel, modelPath );

private:
	virtual void UpdateItSelf( float dTime );
};

