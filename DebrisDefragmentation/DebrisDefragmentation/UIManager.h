#pragma once
#include "DDMacro.h"
#include "Environment.h"

class DDScene;
class DDUIModule;

class UIManager
{
public:
	UIManager();
	~UIManager();

	CREATE_FUNC( UIManager );

	void Init();
	void SetCurrentScene( DDScene* scene ) { m_CurrentScene = scene; }

	void UpdateUI( float dt );

	// generate play scene ui
	void GeneratePlaySceneUI();

private:
	std::map<UIModuleTag, DDUIModule*> m_UIModuleList;
	DDScene* m_CurrentScene = nullptr;
};

extern std::shared_ptr<UIManager> GUIManager;
