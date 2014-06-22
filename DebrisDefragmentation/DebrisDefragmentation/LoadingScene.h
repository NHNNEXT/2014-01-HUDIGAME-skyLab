#pragma once
#include "DDScene.h"
class LoadingScene :
	public DDScene
{
public:
	LoadingScene();
	LoadingScene( std::wstring sceneName );
	virtual ~LoadingScene();

	CREATE_OBJECT_WSTRING( LoadingScene, sceneName );

	void Init();

};

