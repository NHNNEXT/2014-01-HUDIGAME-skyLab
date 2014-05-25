#include "stdafx.h"
#include "InfoPrinter.h"
#include "DDRenderer.h"
#include <d3dx9core.h>

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
	fontParam.Height = 20;
	fontParam.Width = 10;
	fontParam.Weight = 100;
	fontParam.Italic = false;
	fontParam.CharSet = false;
	wcscpy_s( fontParam.FaceName, L"New Roman" );

	//test Rect
	m_pRect = new LPRECT();
	SetRect( *m_pRect, 0, 0, 100, 100 );

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

void InfoPrinter::RenderDebuggingInfo()
{
	// test drawing
	m_pFont->DrawTextW( NULL, L"HelloWorld", -1, *m_pRect, DT_LEFT, D3DCOLOR_ARGB( 0xff, 0xff, 0xff, 0xff ) );
}

void InfoPrinter::RenderItSelf()
{
	RenderDebuggingInfo();
}