#include "stdafx.h"
#include "InfoPrinter.h"
#include "DDRenderer.h"
#include <d3dx9core.h>
#include "GameOption.h"
#include "DebugData.h"

InfoPrinter* GInfoPrinter = nullptr;

InfoPrinter::~InfoPrinter()
{
	m_pFont->Release();
	delete m_pRect;
}

void InfoPrinter::init()
{
	// test param
	D3DXFONT_DESC fontParam;
	ZeroMemory( &fontParam, sizeof( fontParam ) );
	fontParam.Height = 10;
	fontParam.Width = 8;
	fontParam.Weight = 100;
	fontParam.Italic = false;
	fontParam.CharSet = false;
	wcscpy_s( fontParam.FaceName, L"Segoe UI Light" );

	m_pRect = new RECT();
	m_pRect->top = 0;
	m_pRect->bottom = 0;
	m_pRect->left = 0;
	m_pRect->right = 0;

	HRESULT hr = D3DXCreateFontIndirect(
		DDRenderer::GetInstance()->GetDevice(),
		&fontParam,
		&m_pFont
		);

	if ( !SUCCEEDED( hr ) )
	{
		// 디버거 안켜진다고 죽일거 까지 있나... 살려는 드릴게
		assert( false );
	}
}

void InfoPrinter::DrawServerInfo()
{
	std::wstring info = L"SERVER INFO";
	SetRect( m_pRect, 22, 90, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();

	// player's team
	info.append( L"PLAYERS TEAM : \n" );
	for ( int i = 0; i < REAL_PLAYER_NUM; ++i )
	{
		info.append( std::to_wstring( GDebugData->mPlayerTeam[i] ) );
		info.append( L" | " );
	}
	SetRect( m_pRect, 22, 110, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();

	// player's class
	info.append( L"PLAYERS CLASS : \n" );
	for ( int i = 0; i < REAL_PLAYER_NUM; ++i )
	{
		info.append( std::to_wstring( GDebugData->mPlayerClass[i] ) );
		info.append( L" | " );
	}
	SetRect( m_pRect, 22, 140, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();

	// iss position
	info.append( L"ISS POSITION = " );
	info.append( std::to_wstring( GDebugData->mIssPos ) );
	SetRect( m_pRect, 22, 170, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();

	// iss velocity
	info.append( L"ISS VELOCITY = " );
	info.append( std::to_wstring( GDebugData->mIssVelocity ) );
	SetRect( m_pRect, 22, 180, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();

	// iss module owner
	info.append( L"ISS MODULE OWNER\n" );
	for ( int i = 0; i < MODULE_NUMBER; ++i )
	{
		info.append( std::to_wstring( GDebugData->mModuleOwner[i] ) );
		info.append( L"\n" );
	}
	SetRect( m_pRect, 22, 200, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();

	// iss module HP
	info.append( L"ISS MODULE HP\n" );
	for ( int i = 0; i < MODULE_NUMBER; ++i )
	{
		info.append( std::to_wstring( GDebugData->mModuleHP[i] ) );
		info.append( L"\n" );
	}
	SetRect( m_pRect, 22, 320, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();
}

void InfoPrinter::DrawClientInfo()
{
	// client debug info
	int			mClass;

	D3DXVECTOR3 mPos;

	bool	mIsSpin;
	bool	mIsAccelerate;

	D3DXVECTOR3 mForce;
	D3DXVECTOR3 mVelocity;
	D3DXVECTOR3 mSpinAxis;

	float	mSpinAngularVelocity;

	float	mFuel;
	float	mOxygen;
}

void InfoPrinter::RenderItSelf()
{
	DrawServerInfo();
	DrawClientInfo();
}