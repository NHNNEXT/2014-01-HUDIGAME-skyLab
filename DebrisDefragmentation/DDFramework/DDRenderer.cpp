#include "DDRenderer.h"
#include "DDApplication.h"

DDRenderer* DDRenderer::m_pInstance = nullptr;

DDRenderer::DDRenderer()
: m_D3D( NULL ),
m_D3DDevice( NULL )
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

	m_D3D = Direct3DCreate9( D3D_SDK_VERSION );

	ZeroMemory( &m_D3DPresentParameters, sizeof( m_D3DPresentParameters ) );

	D3DMULTISAMPLE_TYPE mst = D3DMULTISAMPLE_NONE;

	m_D3DPresentParameters.Windowed = true;
	m_D3DPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_D3DPresentParameters.BackBufferWidth = DDApplication::GetInstance()->GetScreenWidth();
	m_D3DPresentParameters.BackBufferHeight = DDApplication::GetInstance()->GetScreenHeight();
	m_D3DPresentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_D3DPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	m_D3DPresentParameters.hDeviceWindow = DDApplication::GetInstance()->GetHWND();

	hr = m_D3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, m_D3DPresentParameters.BackBufferFormat, true, mst, NULL );

	if ( SUCCEEDED( hr ) )
	{
		m_D3DPresentParameters.MultiSampleType = mst;
	}
	else
	{
		return false;
	}

	m_D3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DDApplication::GetInstance()->GetHWND(),
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_D3DPresentParameters, &m_D3DDevice ); //D3DCREATE_SOFTWARE_VERTEXPROCESSING

	D3DXCreateSprite( m_D3DDevice, &m_Sprite );

	// m_D3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	// m_D3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	return true;
}

bool DDRenderer::Release()
{
	if ( m_Sprite != NULL )
		m_Sprite->Release();

	if ( m_D3DDevice != NULL )
		m_D3DDevice->Release();

	if ( m_D3D != NULL )
		m_D3D->Release();

	return true;
}

bool DDRenderer::Clear()
{
	if ( NULL == m_D3DDevice )
		return false;

	HRESULT hr = NULL;

	hr = m_D3DDevice->Clear(
		0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );

	if ( FAILED( hr ) )
		return false;

	return true;
}

bool DDRenderer::Begin()
{
	if ( NULL == m_D3DDevice )
		return false;

	if ( SUCCEEDED( m_D3DDevice->BeginScene() ) )
	{
		return true;
	}

	return false;
}

bool DDRenderer::End()
{
	if ( NULL == m_D3DDevice )
		return false;

	HRESULT hr = 0;

	hr = m_D3DDevice->EndScene();
	if ( FAILED( hr ) )
		return false;

	hr = m_D3DDevice->Present( NULL, NULL, NULL, NULL );
	if ( FAILED( hr ) )
		return false;

	return true;
}
