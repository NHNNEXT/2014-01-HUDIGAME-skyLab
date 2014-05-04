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
	// UI Tag == Index
	// UI 객체의 고유 인덱스이기도 하고 UI 파일명 리스트의 인덱스이기도 함
	int index = static_cast<int>( tag );

	// 파일 경로를 만든다
	std::wstring filePath = UI_FILE_PATH;
	filePath.append( UI_FILENAME_LIST[index] );

	// 해당하는 List 인덱스에 UI를 만든다
	m_UIObjectList[index] = DDUI::Create();
	m_UIObjectList[index]->InitUI( filePath );
	m_UIObjectList[index]->SetPosition( x, y, 0 );

	return m_UIObjectList[index];
}
