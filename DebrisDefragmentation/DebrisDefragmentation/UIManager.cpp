#include "stdafx.h"
#include "UIManager.h"
#include "DDScene.h"
#include "DDUIModule.h"

#include "CharacterInfoUI.h"
#include "NavigatorUI.h"

extern std::shared_ptr<UIManager> GUIManager = nullptr;

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
	for ( std::map<UIModuleTag, DDUIModule*>::const_iterator it = m_UIModuleList.begin(); it != m_UIModuleList.end(); ++it )
	{
		delete it->second;
	}
}

void UIManager::Init()
{
	m_CurrentScene = nullptr;
	m_UIModuleList.clear();
}

void UIManager::UpdateUI( float dt )
{
	// 등록된 UI들 update
	for ( std::map<UIModuleTag, DDUIModule*>::const_iterator it = m_UIModuleList.begin(); it != m_UIModuleList.end(); ++it )
	{
		it->second->Update( dt );
	}
}

void UIManager::GeneratePlaySceneUI()
{
	// character info ui
	DDUIModule* characterUI = new CharacterInfoUI();
	characterUI->Init( m_CurrentScene );
	m_UIModuleList.insert( std::map<UIModuleTag, DDUIModule*>::value_type( UIModuleTag::CHARACTER_INFO, characterUI ) );

	// navigator ui
	DDUIModule* navigatorUI = new NavigatorUI();
	navigatorUI->Init( m_CurrentScene );
	m_UIModuleList.insert( std::map<UIModuleTag, DDUIModule*>::value_type( UIModuleTag::NAVIGATOR, navigatorUI ) );

}