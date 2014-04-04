#include "DDSceneDirector.h"

DDSceneDirector* DDSceneDirector::m_pInstance = nullptr;

DDSceneDirector::DDSceneDirector()
: m_pRenderer( nullptr )
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
	m_pRenderer = DDRenderer::GetInstance();

	return true;
}

bool DDSceneDirector::Release()
{
	return true;
}

void DDSceneDirector::UpdateScene( float dt )
{
	
}

void DDSceneDirector::RenderScene()
{
	
}