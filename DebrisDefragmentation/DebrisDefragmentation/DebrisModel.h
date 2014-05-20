#pragma once
#include "DDModel.h"
class DebrisModel :
	public DDModel
{
public:
	DebrisModel();
	virtual ~DebrisModel();

	CREATE_OBJECT( DebrisModel );
	
private:
	virtual void UpdateItSelf( float dTime );

	float tmpTimeCounter;
};
