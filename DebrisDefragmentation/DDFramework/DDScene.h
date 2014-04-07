#pragma once

#include "DDObject.h"
#include "DDPoint.h"
#include "DDInputSystem.h"

class DDScene :
	public DDObject
{
public:
	DDScene();
	virtual ~DDScene();

	static DDScene* Create();

	virtual void Render();
	virtual void Update( float dTime );

	// �ۼ��� : �ְ�� 4.8
	// input : int���� Ű
	// output : ���ڷ� �ѱ� Ű�� ���� ���¸� �޾ƿ��� �Լ�
	KeyState GetKeyState( int key );

	// input : ����
	// output : ���� ���콺 ��ǥ �޾ƿ��� �Լ�
	DDPoint GetMousePosition();

protected:
	DDPoint m_PrevMousePosition;
	// ���⼭ ���߿� skybox ����� �� �� ����(4.6 ��ȯ)
	//LPD3DXSPRITE	m_pSprite;
};

