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
	// 5. 4 문진상
	DDUI*	CreateUI( ClientUITag tag, float x, float y );

	DDUI*	GetUI( ClientUITag tag ) { return m_UIObjectMap[tag] ; }
private:

	//std::array<DDUI*, size_t(ClientUITag::UI_TAG_COUNT)> m_UIObjectList;

	// agebreak : UI의 경우에는 추가/삭제가 빈번할 수 있다. 그리고 인덱스로 구별하는것은 안좋다. map으로 구성한다.
	std::map<ClientUITag, DDUI*> m_UIObjectMap;

};

extern std::shared_ptr<UIManager> g_UIManager;
