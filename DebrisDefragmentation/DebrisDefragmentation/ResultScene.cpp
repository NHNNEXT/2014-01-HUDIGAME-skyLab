#include "stdafx.h"
#include "ResultScene.h"
#include "DDUI.h"


ResultScene::ResultScene()
{
	m_SceneName = L"DefaultResultScene";
}

ResultScene::ResultScene( std::wstring sceneName )
{
	m_SceneName = sceneName;
}


ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
	m_ScreenSaver = DDUI::Create();
	m_ScreenSaver->InitUI( L".\\Resources\\Image\\screen_component\\result.png" );
	m_ScreenSaver->GetTransform().SetScale( 0.6f );
	AddChild( m_ScreenSaver );
}

void ResultScene::UpdateItSelf( float dTime )
{
	m_ScreenSaver->Update( dTime );
}

void ResultScene::RenderItSelf()
{

}
