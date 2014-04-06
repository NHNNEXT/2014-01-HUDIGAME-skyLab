#pragma once

/*
	작성자 : 최경욱
	작성일 : 2014. 4. 6
	내용 : 인풋 값을 업데이트해서 기록하고, 요청받은 키에 대한 현재 상태를 반환 (NNGameFramework와 동일)
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

