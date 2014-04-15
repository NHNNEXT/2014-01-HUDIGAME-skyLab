#pragma once

/*
	�ۼ��� : �ְ��
	�ۼ��� : 2014. 4. 4
	���� : �����ӿ� ����� �Ǵ� application (NNGameFramework�� ���� ����)
*/

#include "DDConfig.h"

// class DDRenderer;
// class DDSceneDirector;

class DDApplication : public Singleton<DDApplication>
{
public:
	// agebreak : ���� ���� �̱��� ������ ���ø�ȭ ���Ѽ� ������ �� �� �ִ� ��ũ���� ����. ���ڸ����� �ڵ带 ���� �ϵ���
	// �̱��� ���ø��� public ��ӹ޴¹������ ������
	DDApplication();
	~DDApplication();

	bool Init( std::wstring title, int width, int height );
	bool Release();
	int Run();

	int GetScreenWidth() const	{ return m_ScreenWidth; }
	int GetScreenHeight() const	{ return m_ScreenHeight; }
	HWND GetHWND() const		{ return m_Hwnd; }

private:

	static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

	bool _CreateWindow( std::wstring title, int width, int height );
	//bool _CreateRenderer();
	void ComputeFPS();

	// agebreak : �̱������� ����� ����, �� ���� ��� ������ �ʿ��Ѱ�?
	// �̱��� ��ü�� ���� �����ϴ� ������� ����(getinstance����� �ְ����� �������̵���...)
// 	std::shared_ptr<DDRenderer>			m_pRenderer;
// 	std::shared_ptr<DDSceneDirector>	m_pSceneDirector;

	// ���α׷� ������ �ڵ�
	HWND m_Hwnd;

	// ���α׷� �ڵ� �޸��� �ڵ�
	HINSTANCE m_hInstance;

	// agebreak : VS 2013���� �Ʒ��� ���� �ʱ�ȭ ���� (C++0x)
	//wchar_t* m_pTitle = nullptr;
	int m_ScreenWidth = 0;
	int m_ScreenHeight = 0;

	float m_Fps = 0.0f;
	float m_FpsTimer = 0.0f;
	float m_ElapsedTime = 0.0f;
	float m_DeltaTime = 0.0f;

	int m_PrevTime = 0;
	int m_NowTime = 0;
	int m_FrameCount = 0;

	bool m_DestroyWindow = false;

};

