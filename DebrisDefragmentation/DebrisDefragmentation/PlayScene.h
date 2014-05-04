#pragma once
#include "DDScene.h"
#include "../external/rapidjson/document.h"

class DDLight;
class Player;

class PlayScene :
	public DDScene
{
public:
	PlayScene();
	PlayScene( std::wstring sceneName );
	virtual ~PlayScene();
		
	//static PlayScene* Create( std::wstring sceneName );
	CREATE_OBJECT_WSTRING( PlayScene , sceneName);

	void Init();


private:
	virtual void UpdateItSelf( float dTime );
	void MousePointer(bool mousePointer, DDPoint  currentMousePos);
	
	// UI 관련 함수들
	void AddUI();
	void UpdateUI();

	// JSON 관련 함수들
	void LoadJSON();

	DDLight*	m_pDirectonalLight = nullptr;

	DDPoint		m_PrevMousePosition{.0f,.0f};

};

