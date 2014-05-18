#pragma once
#include "DDScene.h"
#include "../external/rapidjson/document.h"
#include "ModelPool.h"

class DDLight;
class Player;
class ObjectISS;

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
	ModelPool& GetModelPool() { return m_ModelPool; }

private:
	virtual void UpdateItSelf( float dTime );
	void MousePointer(bool mousePointer, DDPoint  currentMousePos);
	
	// Model 관련 함수
	void InitModelPool();

	// UI 관련 함수들
	void AddUI();
	void UpdateUI();

	// JSON 관련 함수들
	void UpdateISS();

	DDLight*	m_pDirectonalLight = nullptr;
	ModelPool	m_ModelPool;
	DDPoint		m_PrevMousePosition{.0f,.0f};
	ObjectISS*	m_pObjectISS = nullptr;
};

