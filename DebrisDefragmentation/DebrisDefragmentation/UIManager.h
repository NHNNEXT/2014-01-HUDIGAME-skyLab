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
	DDUI*	CreateUIFrame( std::wstring filePath, float x, float y );
	DDUI*	GetUIFuel() const { return m_UIFuel; }
	DDUI*   GetUIOxygen() const { return m_UIOxygen; }
	DDUI*	GetUIFrame() const { return m_UIFrame; }

private:

	// 언젠가 위에 있는 Create 함수를 이 함수 하나로 퉁치는 날이 오길... 일단 못 쓰게 private로 빼놓음
	// 4.29 문진상
	DDUI*	CreateUI( std::wstring filePath, float x, float y );

	DDUI*	m_UIFuel = nullptr;
	DDUI*	m_UIOxygen = nullptr;
	DDUI*	m_UIFrame = nullptr;
};

extern std::shared_ptr<UIManager> g_UIManager;
