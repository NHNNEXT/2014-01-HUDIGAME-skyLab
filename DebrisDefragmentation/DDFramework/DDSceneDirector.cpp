#include "DDSceneDirector.h"
#include "DDConfig.h"

DDSceneDirector* DDSceneDirector::m_pInstance = nullptr;

DDSceneDirector::DDSceneDirector()
{
}

DDSceneDirector::~DDSceneDirector()
{
}

DDSceneDirector* DDSceneDirector::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new DDSceneDirector();
	}

	return m_pInstance;
}

void DDSceneDirector::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

bool DDSceneDirector::Init()
{
	return true;
}

bool DDSceneDirector::Release()
{
	SafeDelete( m_pCurrentScene );
	return true;
}

void DDSceneDirector::UpdateScene( float dt )
{
	if ( nullptr == m_pCurrentScene )
	{
		// error : scene 없음
		return ;
	}

	m_pCurrentScene->Update( dt );

}

void DDSceneDirector::RenderScene()
{
	if ( nullptr == m_pCurrentScene )
	{
		// error : scene 없음
		return;
	}

	m_pCurrentScene->Render();
}

void DDSceneDirector::ChangeScene( DDScene* scene )
{
	if ( m_pCurrentScene == nullptr )
	{
		// error : new scene has a nullptr
		m_pCurrentScene = scene;
	}
	else
	{
		SafeDelete( m_pCurrentScene );
		m_pCurrentScene = scene;
	}
}
