#pragma once
#include "DDConfig.h"

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
	
	// ������!!	
	// scene�� vector�����ɷ� �߰������ϰ� �ƴϸ� map���� name , scene ��� ����ؾ��ҵ�
	// �ϴ��� �׳� logic�״�� �ű�ϴ�. // 4.22 �輺ȯ
	PlayScene*		m_Scene = nullptr;
};

extern std::shared_ptr<SceneManager> g_SceneManager;

