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

class DDInputSystem : public Singleton<DDInputSystem>
{
public:
	DDInputSystem();
	~DDInputSystem();

	void UpdateKeyState();
	KeyState GetKeyState( int key );
	DDPoint GetMousePosition();
	bool IsPressedAnyKey();

private:


	bool m_PrevKeyState[256];
	bool m_NowKeyState[256];
};

