#include "DDSceneDirector.h"

#include "DDConfig.h"
#include "DDScene.h"	

// DDSceneDirector* DDSceneDirector::m_pInstance = nullptr;

DDSceneDirector::DDSceneDirector()
{
}

DDSceneDirector::~DDSceneDirector()
{
}


std::shared_ptr<DDSceneDirector> DDSceneDirector::Create()
{
	return std::shared_ptr<DDSceneDirector>( new DDSceneDirector() );
}


// DDSceneDirector* DDSceneDirector::GetInstance()
// {
// 	if ( m_pInstance == nullptr )
// 	{
// 		m_pInstance = new DDSceneDirector();
// 	}
// 
// 	return m_pInstance;
// }
// 
// void DDSceneDirector::ReleaseInstance()
// {
// 	if ( m_pInstance != nullptr )
// 	{
// 		delete m_pInstance;
// 		m_pInstance = nullptr;
// 	}
// }

bool DDSceneDirector::Init()
{
	return true;
}

bool DDSceneDirector::Release()
{
	// agebreak : �ܺο��� �޾ƿ� Scene�� ���ο��� ���̴� ���� ���� ���� �������ϱ�?
	// scene�� ���ο��� ����ڽ��ϴ�
	SafeDelete( m_pCurrentScene );
	return true;
}

void DDSceneDirector::UpdateScene( float dt )
{
	if ( nullptr == m_pCurrentScene )
	{
		// error : scene ����
		return ;
	}

	m_pCurrentScene->Update( dt );

}

void DDSceneDirector::RenderScene()
{
	if ( nullptr == m_pCurrentScene )
	{
		// error : scene ����
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
		// agebreak : ���� �ܺο��� ���� �ΰ� �����س���, �ʿ��Ҷ����� ü���� �Ѵٸ�??
		// SafeDelete( m_pCurrentScene );
		m_pCurrentScene = scene;
	}
}

void DDSceneDirector::ChangeScene( std::wstring sceneName )
{
	m_pCurrentScene = m_SceneList[sceneName].get();
}

bool DDSceneDirector::CreateScene( std::wstring sceneName )
{
	// ���� �̸��� scene�� �����ϸ� false
	if ( m_SceneList[sceneName] )
	{
		return false;
	}
	
	DDScene* tmpScene = DDScene::Create( sceneName );
	m_SceneList[sceneName] = std::shared_ptr<DDScene>( tmpScene );
	return true;
}

bool DDSceneDirector::DeleteScene( std::wstring sceneName )
{
	// scene�� ������ false
	if ( !m_SceneList[sceneName] )
	{
		return false;
	}
	m_SceneList.erase( sceneName );
}
