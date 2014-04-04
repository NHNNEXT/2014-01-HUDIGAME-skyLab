#pragma once

#include "DDConfig.h"
#include "DDRenderer.h"
#include "DDSceneDirector.h"

class DDApplication
{
public:
	static DDApplication* GetInstance();
	static void ReleaseInstance();

	bool Init( wchar_t* title, int width, int height );
	bool Release();
	int Run();

	int GetScreenWidth() { return m_ScreenWidth; }
	int GetScreenHeight() { return m_ScreenHeight; }
	HWND GetHWND()		{ return m_Hwnd; }

private:
	DDApplication();
	~DDApplication();

	static DDApplication* m_pInstance;
	static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

	bool _CreateWindow( wchar_t* title, int width, int height );
	bool _CreateRenderer();

	DDRenderer* m_pRenderer;
	/* ������ �������̽� */
	DDSceneDirector* m_pSceneDirector;
	/* ���� �����ϴ� �����͸� �����ͷ� �޾ƿ´� */

	HWND m_Hwnd;
	/* ���α׷� �ڵ� */
	HINSTANCE m_hInstance;
	/* ���α׷� �ڵ� �޸��� �ڵ� */

	wchar_t* m_pTitle;
	/* ���α׷��� �̸� */
	int m_ScreenWidth;
	/* ������ �������� �ʺ� */
	int m_ScreenHeight;
	/* ������ �������� ���� */

	float m_Fps;
	/* ���� ������ Frame Per Second, �ʴ� ������ �� */
	float m_FpsTimer;
	/* �� ������ ���� �ֱ�� �������� �����Ѵ� */
	float m_ElapsedTime;
	/* ���α׷��� ���۵� �� ���� �ð� */
	float m_DeltaTime;
	/* ���� �����Ӱ� ���� �������� �ð� �� */

	int m_PrevTime;
	/* �����Ӱ� DeltaTime�� ���ϱ� ���� ���� */
	int m_NowTime;
	/* �����Ӱ� DeltaTime�� ���ϱ� ���� ���� */
	int m_FrameCount;
	/* ������ ī��Ʈ */

	bool m_DestroyWindow;
	/* �����찡 ��������� Ȯ���ϴ� ���� */
};

