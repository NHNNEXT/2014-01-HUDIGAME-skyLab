#include "UIManager.h"
#include "DDUI.h"

extern std::shared_ptr<UIManager> g_UIManager = nullptr;

UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}

DDUI* UIManager::CreateUIOxygen( std::wstring filePath, float x, float y )
{
	m_UIOxygen = DDUI::Create();
	m_UIOxygen->InitUI( filePath );
	m_UIOxygen->SetPosition( x, y, 0 );
	return m_UIOxygen;

}

DDUI* UIManager::CreateUIFuel( std::wstring filePath, float x, float y )
{
	m_UIFuel = DDUI::Create();
	m_UIFuel->InitUI( filePath );
	m_UIFuel->SetPosition( x, y, 0 );
	return m_UIFuel;
}


