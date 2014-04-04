#pragma once

#include "DDConfig.h"
#include "DDRenderer.h"

class DDSceneDirector
{
public:
	static DDSceneDirector* GetInstance();
	static void ReleaseInstance();

	bool Release();
	bool Init();

	void UpdateScene( float dt );
	void RenderScene();

private:
	DDSceneDirector();
	~DDSceneDirector();

	static DDSceneDirector* m_pInstance;
	DDRenderer* m_pRenderer;
};

