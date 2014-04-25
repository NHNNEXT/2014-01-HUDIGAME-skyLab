#pragma once
#include "DDMacro.h"
#include "GameConfig.h"

//전방 선언
class DDUI;

class UIManager
{
public:
	UIManager();
	~UIManager();

	CREATE_FUNC( UIManager );

	// 조심해!!
	// UI들의 자료구조를 정하지 못해서 일단 개별로 생성
	// 나중에 추가로 바꿔야함!!
	// 4.25 김성환
	DDUI*	CreateUIOxygen( std::wstring filePath, float x, float y );
	DDUI*	CreateUIFuel( std::wstring filePath, float x, float y );
	DDUI*	GetUIFuel() const { return m_UIFuel; }
	DDUI*   GetUIOxygen() const { return m_UIOxygen; }

private:
	DDUI*	m_UIFuel = nullptr;
	DDUI*	m_UIOxygen = nullptr;

};

extern std::shared_ptr<UIManager> g_UIManager;
