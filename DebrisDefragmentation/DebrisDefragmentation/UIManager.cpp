#include "stdafx.h"
#include "UIManager.h"

extern std::shared_ptr<UIManager> g_UIManager = nullptr;

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}

DDUI* UIManager::CreateUI( ClientUITag tag, float x, float y )
{
	// agebreak : 기존에는 이미 존재하는 ui를 또 생성요청하면 다시 생성되는 버그가 있다. 
	if (m_UIObjectMap.find(tag) != m_UIObjectMap.end())
	{
		return m_UIObjectMap[tag];
	}

	// UI Tag == Index
	// UI 객체의 고유 인덱스이기도 하고 UI 파일명 리스트의 인덱스이기도 함
	//int index = static_cast<int>( tag );
	
	// agebreak : 맵을 사용하면, int로 변환하지 않아도 된다. 
	// 맵으로 변환하면서 버그의 가능성도 사라지고, 전체적으로 사용이 편해짐

	// 파일 경로를 만든다
	std::wstring filePath = UI_FILE_PATH;
	filePath.append(MAP_UI_FILENAME.at(tag));	

	// 해당하는 List 인덱스에 UI를 만든다
	m_UIObjectMap[tag] = DDUI::Create();
	m_UIObjectMap[tag]->InitUI(filePath);
	m_UIObjectMap[tag]->GetTransform().SetPosition(x, y, 0);

	return m_UIObjectMap[tag];
}
