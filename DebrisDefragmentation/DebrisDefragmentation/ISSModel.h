#pragma once
#include "DDModel.h"
class ISSModel :
	public DDModel
{
public:
	ISSModel( );
	virtual ~ISSModel( );

	CREATE_OBJECT( ISSModel );

private:
	virtual void UpdateItSelf( float dTime );
};

