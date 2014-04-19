#include "DDSceneDirector.h"

#include "DDConfig.h"
#include "DDScene.h"	

DDSceneDirector::DDSceneDirector()
{
}

DDSceneDirector::~DDSceneDirector()
{
}

bool DDSceneDirector::Init()
{
	return true;
}

bool DDSceneDirector::Release()
{
	// agebreak : �ܺο��� �޾ƿ� Scene�� ���ο��� ���̴� ���� ���� ���� �������ϱ�?
	// scene�� ���� �ȿ� �ִ� scene director���� release�ϴ� �ɷ�
	
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