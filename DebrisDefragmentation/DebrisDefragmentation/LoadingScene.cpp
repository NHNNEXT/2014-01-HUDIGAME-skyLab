#include "stdafx.h"
#include "LoadingScene.h"
#include "DDApplication.h"
#include "SoundManager.h"
#include "DDUI.h"


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
	m_ScreenSaver->Release();
}

void LoadingScene::Init()
{
	m_ScreenSaver = DDUI::Create();
	m_ScreenSaver->InitUI( L".\\Resources\\Image\\screen_component\\loading.png" );
	m_ScreenSaver->GetTransform().SetScale( 0.6f );
	AddChild( m_ScreenSaver );

	GSoundManager = SoundManager::Create();
	GSoundManager->Init();
	GSoundManager->PlaySoundW( BGM_LOADING );

}

void LoadingScene::UpdateItSelf( float dTime )
{
	GSoundManager->Update();
	m_ScreenSaver->Update( dTime );
}

void LoadingScene::RenderItSelf()
{
	++m_RenderCount;

	if ( m_RenderCount > 60 )
	{
		PostMessage( DDApplication::GetInstance()->GetHWND(),
			SL_LOADINGSCENE_LOADING_START, NULL, NULL );
	}
}
