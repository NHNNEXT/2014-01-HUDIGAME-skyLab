#include "DDApplication.h"
#include "DDInputSystem.h"

DDApplication* DDApplication::m_pInstance = nullptr;

DDApplication::DDApplication()
{
}

DDApplication::~DDApplication()
{
}

DDApplication* DDApplication::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new DDApplication();
	}

	return m_pInstance;
}

void DDApplication::ReleaseInstance() // agebreak : 쌍이 되는 함수는 같은 위치에 있는 것이 좋음 
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

bool DDApplication::Init( wchar_t* title, int width, int height )
{
	m_hInstance = GetModuleHandle( 0 );

	m_pTitle = title;	// agebreak : 1. 이 코드는 과연 안전한 코드일까? 2. 이 멤버 변수는 굳이 필요할까?
	m_ScreenWidth = width;
	m_ScreenHeight = height;

	// 윈도우와 렌더러 생성
	if ( !_CreateWindow( m_pTitle, m_ScreenWidth, m_ScreenHeight ) ) 
	{
		// 윈도우 생성 실패
		return false;
	}

	if ( !_CreateRenderer() )
	{
		// 렌더러 생성 실패
		return false;
	}

	if ( !m_pRenderer->Init( m_Hwnd ) )
	{
		// 렌더러 초기화 실패
		return false;
	}

	m_pSceneDirector = DDSceneDirector::GetInstance();
	if ( !m_pSceneDirector->Init() )
	{
		// 씬 디렉터 초기화 실패
		return false;
	}

	// random seed 생성
	srand( (unsigned int)time( NULL ) );

	return true;
}


bool DDApplication::_CreateWindow( wchar_t* title, int width, int height )
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = NULL;
	wcex.cbWndExtra = NULL;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = (HBRUSH)( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Debris Defragmentation";
	wcex.hIconSm = NULL;
	wcex.hIcon = NULL;

	RegisterClassEx( &wcex );

	DWORD style = WS_OVERLAPPEDWINDOW;

	RECT wr = { 0, 0, width, height };
	AdjustWindowRect( &wr, WS_OVERLAPPEDWINDOW, FALSE );

	m_Hwnd = CreateWindow( L"Debris Defragmentation", title, style, CW_USEDEFAULT, CW_USEDEFAULT,
						   wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, m_hInstance, NULL );

	ShowWindow( m_Hwnd, SW_SHOWNORMAL );

	return true;
}

bool DDApplication::_CreateRenderer()
{
	m_pRenderer = DDRenderer::GetInstance();

	return true;
}



bool DDApplication::Release()
{
	if ( m_DestroyWindow ) {
		ReleaseInstance();
		return true;
	}

	// agebreak : 싱글톤 = 멤버 변수라니, 이상하지 않은가?
	m_pSceneDirector->Release();
	DDSceneDirector::ReleaseInstance();

	m_pRenderer->Release();
	DDRenderer::ReleaseInstance();

	DDInputSystem::ReleaseInstance();

	ReleaseInstance();

	return true;
}

int DDApplication::Run()
{
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	while ( true )
	{
		// 메세지가 있으면 메세지 처리 루틴으로
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			if ( msg.message == WM_QUIT )
			{
				return true;
			}
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			// agebreak : FPS 구하는 내용이 여기에 구현되어 있을 필요가 있을까? 함수나 클래스로 따로 구현해서 사용하는게 좋음.
			// FPS 구하기
			m_FrameCount++;
			m_NowTime = timeGetTime();

			if ( m_PrevTime == 0.f )
			{
				m_PrevTime = m_NowTime;
			}

			m_DeltaTime = ( static_cast<float>( m_NowTime - m_PrevTime ) ) / 1000.f;
			m_ElapsedTime += m_DeltaTime;
			m_FpsTimer += m_DeltaTime;
			
			if ( m_FpsTimer > 0.1f )
			{
				m_Fps = ( (float)m_FrameCount ) / m_FpsTimer;
				m_FrameCount = 0;
				m_FpsTimer = 0.f;
			}
			m_PrevTime = m_NowTime;

			DDInputSystem::GetInstance()->UpdateKeyState();

			// update scene
			m_pSceneDirector->UpdateScene( m_DeltaTime );

			// display
			if ( true ) // 프레임 수를 조절하려면 여기서 시간 제약을 둬야
			{
				m_pRenderer->Begin( );
				m_pRenderer->Clear( );
				m_pSceneDirector->RenderScene( );
				m_pRenderer->End( );
			}

			if ( DDInputSystem::GetInstance()->GetKeyState( VK_ESCAPE ) == KEY_DOWN )
			{
				PostQuitMessage( 0 );
			}
		}
	}

	return true;
}


LRESULT CALLBACK DDApplication::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch ( message )
	{
	case WM_CREATE:
	{
		break;
	}

	case WM_DESTROY:
	{
		DDApplication::GetInstance()->Release();
		DDApplication::GetInstance()->m_DestroyWindow = true;
		PostQuitMessage( 0 );
		break;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint( hWnd, &ps );
		EndPaint( hWnd, &ps );
		break;
	}

		// 네트웍 이벤트는 여기 추가하시오.

		break;
	}

	return( DefWindowProc( hWnd, message, wParam, lParam ) );
}