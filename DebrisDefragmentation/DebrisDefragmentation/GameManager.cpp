#include "GameManager.h"

GameManager* GameManager::m_pInstance = nullptr;

GameManager* GameManager::GetInstance()
{
	if ( nullptr == m_pInstance )
	{
		m_pInstance = new GameManager();
	}

	return m_pInstance;
}


GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

