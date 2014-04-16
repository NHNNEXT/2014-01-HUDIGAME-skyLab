#include "DDApplication.h"
#include "DDInputSystem.h"
#include "DDRenderer.h"
#include "DDSceneDirector.h"
#include "DDNetwork.h"

#pragma comment(lib,"ws2_32.lib")

DDApplication::DDApplication()
{
}

DDApplication::~DDApplication()
{

}


bool DDApplication::Init( std::wstring title, int width, int height )
{
	m_hInstance = GetModuleHandle( 0 );

	//m_pTitle = title;	// agebreak : 1. �� �ڵ�� ���� ������ �ڵ��ϱ�? 2. �� ��� ������ ���� �ʿ��ұ�?
	// ���� ����, std::wstring���� ����
	m_ScreenWidth = width;
	m_ScreenHeight = height;

	// ������� ������ ����
	//if ( !_CreateWindow( m_pTitle, m_ScreenWidth, m_ScreenHeight ) ) 
	if ( !_CreateWindow( title, m_ScreenWidth, m_ScreenHeight ) )
	{
		// ������ ���� ����
		return false;
	}

// 	if ( !_CreateRenderer() )
// 	{
// 		// ������ ���� ����
// 		return false;
// 	}

	if ( !DDRenderer::GetInstance()->Init( m_Hwnd ) )
	{
		// ������ �ʱ�ȭ ����
		return false;
	}

	
	if ( !DDSceneDirector::GetInstance()->Init() )
	{
		// �� ���� �ʱ�ȭ ����
		return false;
	}

	// random seed ����
	srand( (unsigned int)time( NULL ) );

	DDNetwork::GetInstance()->Init();

	return true;
}


bool DDApplication::_CreateWindow( std::wstring title, int width, int height )
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

	m_Hwnd = CreateWindow( L"Debris Defragmentation", title.c_str(), style, CW_USEDEFAULT, CW_USEDEFAULT,
						   wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, m_hInstance, NULL );

	ShowWindow( m_Hwnd, SW_SHOWNORMAL );

	return true;
}

// bool DDApplication::_CreateRenderer()
// {
// 	// m_pRenderer����
// 	DDRenderer::GetInstance();	
// 
// 	return true;
// }



bool DDApplication::Release()
{
	if ( m_DestroyWindow ) {
		ReleaseInstance();
		return true;
	}

	DDNetwork::ReleaseInstance();

	// agebreak : �̱��� = ��� �������, �̻����� ������?
	DDSceneDirector::GetInstance()->Release();
	DDSceneDirector::ReleaseInstance();

	DDRenderer::GetInstance()->Release();
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
			ComputeFPS();

			DDInputSystem::GetInstance()->UpdateKeyState();

			// update scene
			DDSceneDirector::GetInstance()->UpdateScene( m_DeltaTime );

			// display
			if ( true ) // ������ ���� �����Ϸ��� ���⼭ �ð� ������ �־�
			{
				DDRenderer::GetInstance()->Clear();
				DDRenderer::GetInstance()->Begin();			
				DDSceneDirector::GetInstance()->RenderScene();
				DDRenderer::GetInstance()->End();
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

	case WM_SOCKET:
	{
		if ( WSAGETSELECTERROR( lParam ) )
		{
			MessageBox( hWnd, L"WSAGETSELECTERROR", L"Error", MB_OK | MB_ICONERROR );
			SendMessage( hWnd, WM_DESTROY, NULL, NULL );
			break;
		}

		switch ( WSAGETSELECTEVENT( lParam ) )
		{
		case FD_CONNECT:
		{
							/// NAGLE ����
							/// NAGLE Algorithm
							/// http://en.wikipedia.org/wiki/Nagle's_algorithm
							int opt = 1;
							::setsockopt( DDNetwork::GetInstance()->m_Socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof( int ) );

							int nResult = WSAAsyncSelect( DDNetwork::GetInstance()->m_Socket, hWnd, WM_SOCKET, ( FD_CLOSE | FD_READ | FD_WRITE ) );
							if ( nResult )
							{
								assert( false );
								break;
							}
		}
			break;

		case FD_READ:
		{
						char inBuf[4096] = { 0, };

						int recvLen = recv( DDNetwork::GetInstance()->m_Socket, inBuf, 4096, 0 );

						if ( !DDNetwork::GetInstance()->m_RecvBuffer.Write( inBuf, recvLen ) )
						{
							/// ���� ��á��. 
							assert( false );
						}

						DDNetwork::GetInstance()->ProcessPacket();

		}
			break;

		case FD_WRITE:
		{
						/// ������ ���ۿ� �ִ°͵� ������ ������
			int size = DDNetwork::GetInstance()->m_SendBuffer.GetCurrentSize();
						if ( size > 0 )
						{
							char* data = new char[size];
							DDNetwork::GetInstance()->m_SendBuffer.Peek( data );

							int sent = send( DDNetwork::GetInstance()->m_Socket, data, size, 0 );

							/// �ٸ��� �ִ�
							if ( sent != size )
								OutputDebugStringA( "sent != request\n" );

							DDNetwork::GetInstance()->m_SendBuffer.Consume( sent );

							delete[] data;
						}

		}
			break;

		case FD_CLOSE:
		{
						MessageBox( hWnd, L"Server closed connection", L"Connection closed!", MB_ICONINFORMATION | MB_OK );
						closesocket( DDNetwork::GetInstance()->m_Socket );
						SendMessage( hWnd, WM_DESTROY, NULL, NULL );
		}
			break;
		}
	}
		break;
	}

	return( DefWindowProc( hWnd, message, wParam, lParam ) );
}

void DDApplication::ComputeFPS()
{
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
}

