#pragma once
#include "DDScene.h"

class GameManager
{
public:
	static GameManager* GetInstance();

	void SetCurrentScene( DDScene* scene ) { m_pCurrentScene = scene; }
	DDScene* GetCurrentScene(){ return m_pCurrentScene; }

private:
	GameManager();
	~GameManager();

	static GameManager* m_pInstance;
	DDScene* m_pCurrentScene;
};

