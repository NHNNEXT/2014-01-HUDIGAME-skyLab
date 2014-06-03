#include "stdafx.h"
#include "UIManager.h"
#include "DDScene.h"
#include "DDUI.h"

extern std::shared_ptr<UIManager> GUIManager = nullptr;

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}

void UIManager::Init()
{
	m_CurrentScene = nullptr;
	m_UIObjectMap.clear();
}

void UIManager::UpdateUI( float dt )
{
	// 등록된 UI들 update
	for ( std::map<ClientUITag, DDUI*>::const_iterator it = m_UIObjectMap.begin(); it != m_UIObjectMap.end(); ++it )
	{
		it->second->Update( dt );
	}
}

void UIManager::RegisterUI( ClientUITag tag )
{
	// 기존에 존재하는 UI를 또 생성요청하면 다시 생성되는 버그 방지
	if ( m_UIObjectMap.find( tag ) != m_UIObjectMap.end() )
		return;

	// 파일 경로를 만든다
	std::wstring filePath = UI_FILE_PATH;
	filePath.append( MAP_UI_FILENAME.at( tag ) );

	// 해당하는 List 인덱스에 UI를 만든다
	m_UIObjectMap[tag] = DDUI::Create();
	m_UIObjectMap[tag]->InitUI( filePath );
	// m_UIObjectMap[tag]->GetTransform().SetPosition( x, y, 0 );

	// 그릴 수 있게 현재 씬에 등록
	m_CurrentScene->AddChild( m_UIObjectMap[tag] );
}

void UIManager::DeregisterUI( ClientUITag tag )
{
	if ( m_UIObjectMap.find( tag ) == m_UIObjectMap.end() )
		return;

	// 현재 씬에서 삭제
	assert( m_CurrentScene );
	m_CurrentScene->RemoveChild( m_UIObjectMap[tag] );

	m_UIObjectMap.erase( tag );
}