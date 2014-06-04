#include "stdafx.h"
#include "DDScene.h"
#include "DDApplication.h"


DDScene::DDScene():
m_SceneName( L"DefaultSceneName" )
{
}

DDScene::DDScene( std::wstring sceneName ):
m_SceneName(sceneName)
{

}


DDScene::~DDScene()
{

}


KeyState DDScene::GetKeyState( int key )
{
	if ( ::GetFocus() != DDApplication::GetInstance()->GetHWND() ) 
		return KEY_NOTPRESSED;

	return DDInputSystem::GetInstance()->GetKeyState( key );
}

DDPoint DDScene::GetMousePosition()
{
	if ( ::GetFocus() != DDApplication::GetInstance()->GetHWND() )
		return m_PrevMousePosition;

	return DDInputSystem::GetInstance()->GetMousePosition();
}
