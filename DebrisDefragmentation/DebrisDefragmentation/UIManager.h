#pragma once
#include "DDMacro.h"
#include "GameConfig.h"

//���� ����
class DDUI;

class UIManager
{
public:
	UIManager();
	~UIManager();

	CREATE_FUNC( UIManager );

	// ������!!
	// UI���� �ڷᱸ���� ������ ���ؼ� �ϴ� ������ ����
	// ���߿� �߰��� �ٲ����!!
	// 4.25 �輺ȯ
	DDUI*	CreateUIOxygen( std::wstring filePath, float x, float y );
	DDUI*	CreateUIFuel( std::wstring filePath, float x, float y );
	DDUI*	GetUIFuel() const { return m_UIFuel; }
	DDUI*   GetUIOxygen() const { return m_UIOxygen; }

private:
	DDUI*	m_UIFuel = nullptr;
	DDUI*	m_UIOxygen = nullptr;

};

extern std::shared_ptr<UIManager> g_UIManager;
