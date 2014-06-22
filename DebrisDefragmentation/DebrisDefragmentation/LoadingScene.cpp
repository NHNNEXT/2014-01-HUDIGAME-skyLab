#include "stdafx.h"
#include "LoadingScene.h"
#include "DDApplication.h"


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
	

	PostMessage( DDApplication::GetInstance()->GetHWND(),
		SL_LOADINGSCENE_LOADING_START, NULL, NULL );
}

void LoadingScene::UpdateItSelf( float dTime )
{

}
