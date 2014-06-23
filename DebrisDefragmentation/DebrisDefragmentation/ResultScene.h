#pragma once
#include "DDScene.h"

class DDUI;

class ResultScene :
	public DDScene
{
public:
	ResultScene();
	ResultScene( std::wstring sceneName );
	virtual ~ResultScene();

	CREATE_OBJECT_WSTRING( ResultScene, sceneName );

	virtual void Init();
	virtual void UpdateItSelf( float dTime );

	virtual void RenderItSelf();

private:
	DDUI* m_ScreenSaver = nullptr;
};

