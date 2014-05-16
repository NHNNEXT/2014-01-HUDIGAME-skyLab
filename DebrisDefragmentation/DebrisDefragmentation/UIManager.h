#pragma once
#include "DDMacro.h"
#include "DDUI.h"
#include "Environment.h"

class UIManager
{
public:
	UIManager();
	~UIManager();

	CREATE_FUNC( UIManager );

	// 바꿨슴다
	DDUI*	CreateUI( ClientUITag tag, float x, float y );

	DDUI*	GetUI( ClientUITag tag ) { return m_UIObjectMap[tag]; }
private:

	std::map<ClientUITag, DDUI*> m_UIObjectMap;

};

extern std::shared_ptr<UIManager> g_UIManager;
