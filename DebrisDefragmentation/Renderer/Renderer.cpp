// Renderer.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "Renderer.h"
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 )
#pragma comment(lib, "winmm.lib")

LPDIRECT3D9             g_pD3D = NULL;
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;

bool Init( HWND hWnd, int WindowWidth, int WindowHeight )
{
	HRESULT hr = 0;

	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	D3DPRESENT_PARAMETERS D3DPresentParameters;
	ZeroMemory( &D3DPresentParameters, sizeof( D3DPresentParameters ) );

	D3DMULTISAMPLE_TYPE mst = D3DMULTISAMPLE_NONE;

	D3DPresentParameters.Windowed = TRUE;
	D3DPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3DPresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	D3DPresentParameters.BackBufferWidth = WindowWidth;
	D3DPresentParameters.BackBufferHeight = WindowHeight;
	D3DPresentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	D3DPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//m_D3DPresentParameters.hDeviceWindow = DDApplication::GetInstance()->GetHWND();

	hr = g_pD3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, D3DPresentParameters.BackBufferFormat, true, mst, NULL );

	if ( SUCCEEDED( hr ) )
	{
		D3DPresentParameters.MultiSampleType = mst;
	}
	else
	{
		return false;
	}

	g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &D3DPresentParameters, &g_pd3dDevice ); //D3DCREATE_SOFTWARE_VERTEXPROCESSING

	return true;
}

bool Release()
{
	if ( g_pd3dDevice != NULL )
		g_pd3dDevice->Release();

	if ( g_pD3D != NULL )
		g_pD3D->Release();

	return true;
}

bool Clear()
{
	if ( NULL == g_pd3dDevice )
		return false;

	HRESULT hr = NULL;

	hr = g_pd3dDevice->Clear(
		0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );

	if ( FAILED( hr ) )
		return false;

	return true;
}

bool Begin()
{
	if ( NULL == g_pd3dDevice )
		return false;

	if ( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
	{
		return true;
	}

	return false;
}

bool End()
{
	if ( NULL == g_pd3dDevice )
		return false;

	HRESULT hr = 0;

	hr = g_pd3dDevice->EndScene();
	if ( FAILED( hr ) )
		return false;

	hr = g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
	if ( FAILED( hr ) )
		return false;

	return true;
}
