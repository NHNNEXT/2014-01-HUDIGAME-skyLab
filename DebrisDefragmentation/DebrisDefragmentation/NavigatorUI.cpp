#include "stdafx.h"
#include "NavigatorUI.h"


NavigatorUI::NavigatorUI()
{
}


NavigatorUI::~NavigatorUI()
{
}

bool NavigatorUI::GenerateUI()
{
	// 하나씩 만들어서 m_UIComponentList에 추가한다.
	/*
	std::wstring filePath = UI_FILE_PATH;
	filePath.append( MAP_UI_FILENAME.at( tag ) );

	// 해당하는 List 인덱스에 UI를 만든다
	m_UIObjectMap[tag] = DDUI::Create();
	m_UIObjectMap[tag]->InitUI( filePath );
	*/

	return true;
}

void NavigatorUI::Update( float dt )
{

}