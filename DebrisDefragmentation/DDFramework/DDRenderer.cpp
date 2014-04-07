#include "DDRenderer.h"
#include "DDApplication.h"

DDRenderer* DDRenderer::m_pInstance = nullptr;

DDRenderer::DDRenderer()
: m_pD3D( NULL ),
m_pD3DDevice( NULL )
{
}

DDRenderer::~DDRenderer()
{
}

DDRenderer* DDRenderer::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new DDRenderer();
	}

	return m_pInstance;
}

void DDRenderer::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

bool DDRenderer::Init( HWND hWnd )
{
	HRESULT hr = 0;

	if ( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
		return false;
	}

	ZeroMemory( &m_D3DPresentParameters, sizeof( m_D3DPresentParameters ) );

	D3DMULTISAMPLE_TYPE mst = D3DMULTISAMPLE_NONE;

	m_D3DPresentParameters.Windowed = TRUE;
	m_D3DPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPresentParameters.EnableAutoDepthStencil = TRUE;
	m_D3DPresentParameters.AutoDepthStencilFormat = D3DFMT_D16; // 16-bit z-buffer bit depth.
	m_D3DPresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_D3DPresentParameters.BackBufferWidth = DDApplication::GetInstance()->GetScreenWidth();
	m_D3DPresentParameters.BackBufferHeight = DDApplication::GetInstance()->GetScreenHeight();
	m_D3DPresentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_D3DPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	m_D3DPresentParameters.hDeviceWindow = DDApplication::GetInstance()->GetHWND();

	hr = m_pD3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, m_D3DPresentParameters.BackBufferFormat, true, mst, NULL );

	if ( FAILED( hr ) )
	{
		return false;
	}

	m_D3DPresentParameters.MultiSampleType = mst;

	hr = m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DDApplication::GetInstance()->GetHWND(),
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_D3DPresentParameters, &m_pD3DDevice ); //D3DCREATE_SOFTWARE_VERTEXPROCESSING

	if ( FAILED( hr ) )
	{
		return false;
	}

	hr = D3DXCreateSprite( m_pD3DDevice, &m_pSprite );
	
	if ( FAILED( hr ) )
	{
		return false;
	}

	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	return true;
}

bool DDRenderer::Release()
{
	if ( m_pSprite != NULL )
		m_pSprite->Release();

	if ( m_pD3DDevice != NULL )
		m_pD3DDevice->Release();

	if ( m_pD3D != NULL )
		m_pD3D->Release();

	return true;
}

bool DDRenderer::Clear()
{
	if ( NULL == m_pD3DDevice )
		return false;

	HRESULT hr = NULL;

	hr = m_pD3DDevice->Clear(
		0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );

	if ( FAILED( hr ) )
		return false;

	return true;
}

bool DDRenderer::Begin()
{
	if ( NULL == m_pD3DDevice )
		return false;

	if ( FAILED( m_pD3DDevice->BeginScene() ) )
		return false;
	

	return true;
}

bool DDRenderer::End()
{
	if ( NULL == m_pD3DDevice )
		return false;

	HRESULT hr = 0;

	hr = m_pD3DDevice->EndScene();
	if ( FAILED( hr ) )
		return false;

	hr = m_pD3DDevice->Present( NULL, NULL, NULL, NULL );
	if ( FAILED( hr ) )
		return false;

	return true;
}
