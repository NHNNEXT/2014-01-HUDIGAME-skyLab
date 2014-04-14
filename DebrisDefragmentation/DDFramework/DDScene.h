#pragma once

#include "DDObject.h"
#include "DDPoint.h"
#include "DDInputSystem.h"

class DDScene :
	public DDObject
{
public:
	DDScene();
	DDScene(std::wstring sceneName);
	virtual ~DDScene();

	static DDScene* Create(std::wstring sceneName);
	
	std::wstring GetSceneName() const { return m_SceneName; }
	void SetSceneName( std::wstring val ) { m_SceneName = val; }

protected:	
	// �ۼ��� : �ְ�� 4.8
	// input : int���� Ű
	// output : ���ڷ� �ѱ� Ű�� ���� ���¸� �޾ƿ��� �Լ�
	KeyState	GetKeyState( int key );

	// input : ����
	// output : ���� ���콺 ��ǥ �޾ƿ��� �Լ�
	DDPoint		GetMousePosition();
	

	// ���⼭ ���߿� skybox ����� �� �� ����(4.6 ��ȯ)
	//LPD3DXSPRITE	m_pSprite;

	// scene�� �����ϱ� ���� �̸�
	std::wstring m_SceneName;
};

