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

	virtual void Init();
	virtual void UpdateItSelf( float dTime );

};

