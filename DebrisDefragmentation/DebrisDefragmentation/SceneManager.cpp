#include "stdafx.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include "DDScene.h"
#include "LoadingScene.h"
#include "ResultScene.h"

std::shared_ptr<SceneManager> GSceneManager = nullptr;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

DDScene* SceneManager::CreateScene( std::wstring sceneName, SceneType scene )
{
	switch ( scene )
	{
	case SceneType::LOADING_SCENE:
		m_LoadingScene = LoadingScene::Create( sceneName );
		m_LoadingScene->Init();
		return m_LoadingScene;
	case SceneType::PLAY_SCENE:
		m_PlayScene = PlayScene::Create( sceneName );
		m_PlayScene->Init();
		return m_PlayScene;
	case SceneType::RESULT_SCENE:
		m_ResultScene = ResultScene::Create( sceneName );
		m_ResultScene->Init();
		return m_ResultScene;
	default:
		return nullptr;
	}
	
}