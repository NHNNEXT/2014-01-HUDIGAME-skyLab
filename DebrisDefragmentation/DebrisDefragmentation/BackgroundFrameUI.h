#pragma once

#include "DDUIModule.h"

class BackgroundFrameUI :
	public DDUIModule
{
public:
	BackgroundFrameUI();
	virtual ~BackgroundFrameUI();

	bool GenerateUI();

	void Update( float dt );
};

