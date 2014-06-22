#include "stdafx.h"
#include "LoadingScene.h"


LoadingScene::LoadingScene()
{
	m_SceneName = L"DefaultLoadingScene";
}

LoadingScene::LoadingScene( std::wstring sceneName )
{
	m_SceneName = sceneName;
}


LoadingScene::~LoadingScene()
{
}

void LoadingScene::Init()
{

}
