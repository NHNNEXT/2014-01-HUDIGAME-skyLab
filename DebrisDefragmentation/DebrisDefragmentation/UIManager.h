#pragma once
#include "DDMacro.h"
#include "GameConfig.h"
#include "DDUI.h"
#include "GameOption.h"

class UIManager
{
public:
	UIManager();
	~UIManager();

	CREATE_FUNC( UIManager );

	// 바꿨슴다
	// 5. 4 문진상
	DDUI*	CreateUI( ClientUITag tag, float x, float y );

	DDUI*	GetUI( ClientUITag tag ) { return m_UIObjectList[static_cast<int>(tag)]; }
private:

	std::array<DDUI*, size_t(ClientUITag::UI_TAG_COUNT)> m_UIObjectList;

};

extern std::shared_ptr<UIManager> g_UIManager;
