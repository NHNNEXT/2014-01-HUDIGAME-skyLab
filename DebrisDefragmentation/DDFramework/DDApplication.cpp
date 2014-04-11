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

void DDApplication::ReleaseInstance() // agebreak : ���� �Ǵ� �Լ��� ���� ��ġ�� �ִ� ���� ���� 
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

	m_pTitle = title;	// agebreak : 1. �� �ڵ�� ���� ������ �ڵ��ϱ�? 2. �� ��� ������ ���� �ʿ��ұ�?
	m_ScreenWidth = width;
	m_ScreenHeight = height;

	// ������� ������ ����
	if ( !_CreateWindow( m_pTitle, m_ScreenWidth, m_ScreenHeight ) ) 
	{
		// ������ ���� ����
		return false;
	}

	if ( !_CreateRenderer() )
	{
		// ������ ���� ����
		return false;
	}

	if ( !m_pRenderer->Init( m_Hwnd ) )
	{
		// ������ �ʱ�ȭ ����
		return false;
	}

	m_pSceneDirector = DDSceneDirector::GetInstance();
	if ( !m_pSceneDirector->Init() )
	{
		// �� ���� �ʱ�ȭ ����
		return false;
	}

	// random seed ����
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

	// agebreak : �̱��� = ��� �������, �̻����� ������?
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
		// �޼����� ������ �޼��� ó�� ��ƾ����
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
			// agebreak : FPS ���ϴ� ������ ���⿡ �����Ǿ� ���� �ʿ䰡 ������? �Լ��� Ŭ������ ���� �����ؼ� ����ϴ°� ����.
			// FPS ���ϱ�
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
			if ( true ) // ������ ���� �����Ϸ��� ���⼭ �ð� ������ �־�
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

		// ��Ʈ�� �̺�Ʈ�� ���� �߰��Ͻÿ�.

		break;
	}

	return( DefWindowProc( hWnd, message, wParam, lParam ) );
}