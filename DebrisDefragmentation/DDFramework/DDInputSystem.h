#pragma once

/*
	�ۼ��� : �ְ��
	�ۼ��� : 2014. 4. 6
	���� : ��ǲ ���� ������Ʈ�ؼ� ����ϰ�, ��û���� Ű�� ���� ���� ���¸� ��ȯ (NNGameFramework�� ����)
*/
#include "DDConfig.h"
#include "DDPoint.h"

enum KeyState
{
	KEY_DOWN,
	KEY_PRESSED,
	KEY_UP,
	KEY_NOTPRESSED,
};

class DDInputSystem
{
public:
	static DDInputSystem* GetInstance();
	static void ReleaseInstance();

	void UpdateKeyState();
	KeyState GetKeyState( int key );
	DDPoint GetMousePosition();
	bool IsPressedAnyKey();

private:
	DDInputSystem();
	~DDInputSystem();

	static DDInputSystem* m_pInstance;

	bool m_PrevKeyState[256];
	bool m_NowKeyState[256];
};

