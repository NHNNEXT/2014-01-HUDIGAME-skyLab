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
	/* 렌더러 인터페이스 */
	DDSceneDirector* m_pSceneDirector;
	/* 씬을 관리하는 씬디렉터를 포인터로 받아온다 */

	HWND m_Hwnd;
	/* 프로그램 핸들 */
	HINSTANCE m_hInstance;
	/* 프로그램 코드 메모리의 핸들 */

	wchar_t* m_pTitle;
	/* 프로그램의 이름 */
	int m_ScreenWidth;
	/* 윈도우 프레임의 너비 */
	int m_ScreenHeight;
	/* 윈도우 프레임의 높이 */

	float m_Fps;
	/* 게임 루프의 Frame Per Second, 초당 프레임 수 */
	float m_FpsTimer;
	/* 이 변수의 값을 주기로 프레임을 측정한다 */
	float m_ElapsedTime;
	/* 프로그램이 시작된 후 지난 시간 */
	float m_DeltaTime;
	/* 이전 프레임과 현재 프레임의 시간 차 */

	int m_PrevTime;
	/* 프레임과 DeltaTime을 구하기 위한 변수 */
	int m_NowTime;
	/* 프레임과 DeltaTime을 구하기 위한 변수 */
	int m_FrameCount;
	/* 프레임 카운트 */

	bool m_DestroyWindow;
	/* 윈도우가 삭제됬는지 확인하는 변수 */
};

