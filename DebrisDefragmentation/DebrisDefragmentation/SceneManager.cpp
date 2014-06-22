#include "stdafx.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include "DDScene.h"
#include "LoadingScene.h"
#include "ResultScene.h"
#include "DDSceneDirector.h"

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
		CreateScene( L"PlayScene", SceneType::PLAY_SCENE);
		AddSceneToDirector( m_LoadingScene );
		return m_LoadingScene;
	case SceneType::PLAY_SCENE:
		m_PlayScene = PlayScene::Create( sceneName );
		AddSceneToDirector( m_PlayScene );
		return m_PlayScene;
	case SceneType::RESULT_SCENE:
		m_ResultScene = ResultScene::Create( sceneName );
		AddSceneToDirector( m_ResultScene );
		return m_ResultScene;
	default:
		return nullptr;
	}
	
}

void SceneManager::AddSceneToDirector( DDScene* scene )
{
	DDSceneDirector::GetInstance()->AddScene( scene );
}

void SceneManager::ClearAllScene()
{
	if ( m_LoadingScene )
	{
		m_LoadingScene->Release();
		m_LoadingScene = nullptr;
	}

	if ( m_PlayScene )
	{
		m_PlayScene->Release();
		m_PlayScene = nullptr;
	}

	if ( m_ResultScene )
	{
		m_ResultScene->Release();
		m_ResultScene = nullptr;
	}
}