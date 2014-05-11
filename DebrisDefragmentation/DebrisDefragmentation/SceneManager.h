#pragma once
#include "GameMacro.h"
#include <string>

class PlayScene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	CREATE_FUNC( SceneManager );

	PlayScene*	CreateScene( std::wstring sceneName );
	PlayScene*	GetScene() const { return m_Scene; }


private :
	
	// 조심해!!	
	// scene을 vector같은걸로 추가가능하게 아니면 map으로 name , scene 묶어서 사용해야할듯
	// 최카멕 : 스택을 써!
	// 일단은 그냥 logic그대로 옮깁니다. // 4.22 김성환
	PlayScene*		m_Scene = nullptr;
};

extern std::shared_ptr<SceneManager> g_SceneManager;

