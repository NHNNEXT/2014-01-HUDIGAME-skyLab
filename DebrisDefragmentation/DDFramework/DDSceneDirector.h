#pragma once

#include "DDConfig.h"
#include "DDMacro.h"

// agebreak : 전방 선언을 활용하면 Include 할 필요가 없다
// 전방 선언
class DDScene;

// agebreak : 씬으로 구별하고, 씬디렉터를 두는 프레임워크 구조는 좋은 구조!
class DDSceneDirector : public Singleton<DDSceneDirector>
{
public:
	DDSceneDirector();
	~DDSceneDirector();

	bool Release();
	bool Init();

	void ChangeScene( DDScene* scene );
	void ChangeScene( std::wstring sceneName );
	
	DDScene* GetCurrentScene() { return m_pCurrentScene; }
	
	void UpdateScene( float dt );
	void RenderScene();
	void AddScene( DDScene* scene );

private:
	std::unordered_map<std::wstring, std::shared_ptr<DDScene>> m_SceneList;	
	DDScene*				m_pCurrentScene = nullptr;
};

