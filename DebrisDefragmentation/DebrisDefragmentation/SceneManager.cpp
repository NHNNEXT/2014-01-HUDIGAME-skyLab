#include "SceneManager.h"
#include "PlayScene.h"

std::shared_ptr<SceneManager> g_SceneManager = nullptr;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

PlayScene* SceneManager::CreateScene( std::wstring sceneName )
{
	m_Scene = PlayScene::Create( sceneName );
	m_Scene->Init();
	return m_Scene;
}