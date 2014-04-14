#pragma once

#include "DDConfig.h"

// agebreak : ���� ������ Ȱ���ϸ� Include �� �ʿ䰡 ����
// ���� ����
class DDScene;

// agebreak : ������ �����ϰ�, �����͸� �δ� �����ӿ�ũ ������ ���� ����!
class DDSceneDirector : public Singleton<DDSceneDirector>
{
public:
	DDSceneDirector();
	~DDSceneDirector();

	bool Release();
	bool Init();

	void ChangeScene( DDScene* scene );	

	// ������!!
	// �ڽ� Ŭ�������� �� ���� ����. �ܺο��� �������ϳ� �� 
// 	void ChangeScene( std::wstring sceneName );
// 	bool CreateScene( std::wstring sceneName );
// 	bool DeleteScene( std::wstring sceneName );
	// ��� ��

	DDScene* GetCurrentScene() { return m_pCurrentScene; }
	
	void UpdateScene( float dt );
	void RenderScene();

private:
	std::map<std::wstring, std::shared_ptr<DDScene>> m_SceneList;	
	DDScene*				m_pCurrentScene = nullptr;
};

