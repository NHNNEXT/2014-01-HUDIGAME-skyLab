#pragma once

/*
	작성자 : 최경욱
	작성일 : 2014. 4. 4
	내용 : 프레임웍 기반이 되는 application (NNGameFramework와 거의 동일)
*/

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
	DDSceneDirector* m_pSceneDirector;

	// 프로그램 윈도우 핸들
	HWND m_Hwnd;

	// 프로그램 코드 메모리의 핸들
	HINSTANCE m_hInstance;

	wchar_t* m_pTitle;
	int m_ScreenWidth;
	int m_ScreenHeight;

	float m_Fps;
	float m_FpsTimer;
	float m_ElapsedTime;
	float m_DeltaTime;

	int m_PrevTime;
	int m_NowTime;
	int m_FrameCount;

	bool m_DestroyWindow;
};

