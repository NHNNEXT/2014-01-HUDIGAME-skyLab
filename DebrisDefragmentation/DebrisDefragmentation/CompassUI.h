#pragma once
#include "DDModel.h"
class CompassUI :
	public DDModel
{
public:
	CompassUI();
	CompassUI( std::wstring modelPath );
	virtual ~CompassUI();

	CREATE_OBJECT_WSTRING( CompassUI, modelPath );

private:
	virtual void UpdateItSelf( float dTime );
	//virtual void RenderItSelf();
};