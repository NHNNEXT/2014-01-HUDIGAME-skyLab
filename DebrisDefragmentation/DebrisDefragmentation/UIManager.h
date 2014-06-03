#pragma once
#include "DDMacro.h"
#include "Environment.h"

class DDScene;
class DDUI;

class UIManager
{
public:
	UIManager();
	~UIManager();

	CREATE_FUNC( UIManager );

	void Init();
	void SetCurrentScene( DDScene* scene ) { m_CurrentScene = scene; }

	void UpdateUI( float dt );

	// 바꿨슴다
	void RegisterUI( ClientUITag tag );
	void DeregisterUI( ClientUITag tag );

private:
	std::map<ClientUITag, DDUI*> m_UIObjectMap;
	DDScene* m_CurrentScene = nullptr;
};

extern std::shared_ptr<UIManager> GUIManager;
