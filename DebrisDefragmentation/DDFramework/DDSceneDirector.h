#pragma once

#include "DDConfig.h"
#include "DDRenderer.h"
#include "DDScene.h"

class DDSceneDirector
{
public:
	static DDSceneDirector* GetInstance();
	static void ReleaseInstance();

	bool Release();
	bool Init();

	void ChangeScene( DDScene* scene );
	void UpdateScene( float dt );
	void RenderScene();

	DDScene* GetCurrentScene() { return m_pCurrentScene; }

private:
	DDSceneDirector();
	~DDSceneDirector();

	static DDSceneDirector* m_pInstance;	
	DDScene*		m_pCurrentScene;
};

