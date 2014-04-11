#pragma once

#include "DDConfig.h"
#include "DDRenderer.h"
#include "DDScene.h"	// agebreak : 전방 선언을 활용하면 Include 할 필요가 없다

// agebreak : 씬으로 구별하고, 씬디렉터를 두는 프레임워크 구조는 좋은 구조!
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

