#include "stdafx.h"
#include "InfoPrinter.h"
#include "DDRenderer.h"
#include <d3dx9core.h>
#include "GameOption.h"
#include "DebugData.h"
#include "PlayerManager.h"

InfoPrinter* GInfoPrinter = nullptr;

InfoPrinter::~InfoPrinter()
{
	m_pCharacterStatusFont->Release();
	m_pNavigationFont->Release();

	m_pFont->Release();
	delete m_pRect;
}

void InfoPrinter::init()
{
	// test param
	m_pRect = new RECT();
	m_pRect->top = 0;
	m_pRect->bottom = 0;
	m_pRect->left = 0;
	m_pRect->right = 0;

	D3DXFONT_DESC fontParam;
	ZeroMemory( &fontParam, sizeof( fontParam ) );
	fontParam.Height = 10;
	fontParam.Width = 8;
	fontParam.Weight = 100;
	fontParam.Italic = false;
	fontParam.CharSet = false;
	wcscpy_s( fontParam.FaceName, L"Segoe UI Light" );

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

	ZeroMemory( &fontParam, sizeof( fontParam ) );
	fontParam.Height = 22;
	fontParam.Width = 20;
	fontParam.Weight = 150;
	fontParam.Italic = false;
	fontParam.CharSet = false;
	wcscpy_s( fontParam.FaceName, L"Segoe UI Light" );

	hr = D3DXCreateFontIndirect(
		DDRenderer::GetInstance()->GetDevice(),
		&fontParam,
		&m_pCharacterStatusFont
		);

	if ( !SUCCEEDED( hr ) )
	{
		assert( false );
	}

	ZeroMemory( &fontParam, sizeof( fontParam ) );
	fontParam.Height = 12;
	fontParam.Width = 12;
	fontParam.Weight = 100;
	fontParam.Italic = false;
	fontParam.CharSet = false;
	wcscpy_s( fontParam.FaceName, L"Segoe UI Light" );

	hr = D3DXCreateFontIndirect(
		DDRenderer::GetInstance()->GetDevice(),
		&fontParam,
		&m_pNavigationFont
		);

	if ( !SUCCEEDED( hr ) )
	{
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
	std::wstring info = L"CHARACTER INFO";
	SetRect( m_pRect, 280, 90, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();

	// player's id and class
	info.append( L"PLAYER'S ID : " );
	info.append( std::to_wstring( GDebugData->mPlayerId ) );
	info.append( L"\nPLAYER'S CLASS : " );
	info.append( std::to_wstring( GDebugData->mClass ) );
	SetRect( m_pRect, 280, 110, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();

	// player's position
	info.append( L"PLAYER'S POSITION : \n" );
	info.append( std::to_wstring( GDebugData->mPos.x ) ); 
	info.append( L" | " );
	info.append( std::to_wstring( GDebugData->mPos.y ) );
	info.append( L" | " );
	info.append( std::to_wstring( GDebugData->mPos.z ) );
	SetRect( m_pRect, 280, 140, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();

	// player's kinetic state
	info.append( L"SPIN : " );
	info.append( std::to_wstring( GDebugData->mIsSpin ) );
	info.append( L"\nACCELERATION : " );
	info.append( std::to_wstring( GDebugData->mIsAccelerate ) );
	SetRect( m_pRect, 280, 170, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();

	// player's speed constant
	info.append( L"PLAYER'S SPEED CONSTANT : " );
	info.append( std::to_wstring( GDebugData->mSpeedConstant ) );
	SetRect( m_pRect, 280, 190, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str( ), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear( );

	// player's acceleration state
	info.append( L"ACCELERATION : \n" );
	info.append( std::to_wstring( GDebugData->mAcceleration.x ) );
	info.append( L" | " );
	info.append( std::to_wstring( GDebugData->mAcceleration.y ) );
	info.append( L" | " );
	info.append( std::to_wstring( GDebugData->mAcceleration.z ) );
	SetRect( m_pRect, 280, 220, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();

	// player's velocity state
	info.append( L"VELOCITY : \n" );
	info.append( std::to_wstring( GDebugData->mVelocity.x ) );
	info.append( L" | " );
	info.append( std::to_wstring( GDebugData->mVelocity.y ) );
	info.append( L" | " );
	info.append( std::to_wstring( GDebugData->mVelocity.z ) );
	SetRect( m_pRect, 280, 250, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();

	// player's spin axis
	info.append( L"SPIN AXIS : \n" );
	info.append( std::to_wstring( GDebugData->mSpinAxis.x ) );
	info.append( L" | " );
	info.append( std::to_wstring( GDebugData->mSpinAxis.y ) );
	info.append( L" | " );
	info.append( std::to_wstring( GDebugData->mSpinAxis.z ) );
	SetRect( m_pRect, 280, 280, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();

	// player's angular velocity
	info.append( L"SPIN ANGULAR VELOCITY : " );
	info.append( std::to_wstring( GDebugData->mSpinAngularVelocity ) );
	SetRect( m_pRect, 280, 310, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();

	// player's character state
	info.append( L"FUEL : " );
	info.append( std::to_wstring( GDebugData->mFuel ) );
	info.append( L"\nOXYGEN : " );
	info.append( std::to_wstring( GDebugData->mOxygen ) );
	SetRect( m_pRect, 280, 330, 1000, 1000 );
	m_pFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
	info.clear();
}

void InfoPrinter::RenderItSelf()
{
	if ( GPlayerManager->GetMyPlayer() )
	{
		// fuel
		std::wstring info = L"";
		info.append( std::to_wstring( static_cast<int>( static_cast<int>( GPlayerManager->GetMyPlayer()->GetClassComponent()->GetFuel() * 100 / DEFAULT_FUEL ) ) ) );
		info.append( L"\%" );
		SetRect( m_pRect, 0, 320, 227, 1000 );
		m_pCharacterStatusFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_RIGHT, D3DCOLOR_ARGB( 0xbb, 0xff, 0xff, 0xff ) );
		info.clear();

		// oxygen
		info.append( std::to_wstring( static_cast<int>( static_cast<int>( GPlayerManager->GetMyPlayer()->GetClassComponent()->GetOxygen() * 100 / DEFAULT_OXYGEN ) ) ) );
		info.append( L"\%" );
		SetRect( m_pRect, 0, 388, 227, 1000 );
		m_pCharacterStatusFont->DrawTextW( NULL, info.c_str(), -1, m_pRect, DT_RIGHT, D3DCOLOR_ARGB( 0xbb, 0xff, 0xff, 0xff ) );
		info.clear();

		// navigation
	}

	if ( !GDebugData->mDisplayDebugInfoFlag )
		return;

	DrawServerInfo();
	DrawClientInfo();
}