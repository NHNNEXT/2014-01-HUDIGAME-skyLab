#pragma once

#include "DDUI.h"

class NavigatorUI :
	public DDUI
{
public:
	NavigatorUI();
	virtual ~NavigatorUI();

	void Init();

	CREATE_OBJECT( NavigatorUI );

private:
	virtual void UpdateItSelf( float dTime );
	virtual void RenderItSelf();
};

