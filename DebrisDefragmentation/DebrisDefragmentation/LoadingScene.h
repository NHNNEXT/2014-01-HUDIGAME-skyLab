#pragma once
#include "DDScene.h"

class DDUI;

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

	virtual void RenderItSelf();

private:
	DDUI* m_ScreenSaver = nullptr;
	int m_RenderCount = 0;
};

