#include "stdafx.h"
#include "DDInputSystem.h"
#include "DDApplication.h"
#include <windows.h>

DDInputSystem* DDInputSystem::m_pInstance = nullptr;

DDInputSystem::DDInputSystem()
{
	ZeroMemory( m_PrevKeyState, sizeof( m_PrevKeyState ) );
	ZeroMemory( m_NowKeyState, sizeof( m_NowKeyState ) );
}

DDInputSystem::~DDInputSystem()
{
}

DDInputSystem* DDInputSystem::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new DDInputSystem();
	}

	return m_pInstance;
}
void DDInputSystem::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void DDInputSystem::UpdateKeyState()
{
	if ( GetFocus() == NULL ) return;

	for ( int i = 0; i<256; i++ )
	{
		m_PrevKeyState[i] = m_NowKeyState[i];

		if ( ::GetKeyState( i ) & 0x8000 )
		{
			m_NowKeyState[i] = true;
		}
		else
		{
			m_NowKeyState[i] = false;
		}
	}
}

KeyState DDInputSystem::GetKeyState( int key )
{
	if ( m_PrevKeyState[key] == false && m_NowKeyState[key] == true )
	{
		return KEY_DOWN;
	}
	else if ( m_PrevKeyState[key] == true && m_NowKeyState[key] == true )
	{
		return KEY_PRESSED;
	}
	else if ( m_PrevKeyState[key] == true && m_NowKeyState[key] == false )
	{
		return KEY_UP;
	}

	return KEY_NOTPRESSED;
}

DDPoint DDInputSystem::GetMousePosition()
{
	POINT pt;
	GetCursorPos( &pt );
	ScreenToClient( DDApplication::GetInstance()->GetHWND(), &pt );

	return DDPoint( (float)pt.x, (float)pt.y );
}

bool DDInputSystem::IsPressedAnyKey()
{
	for ( int i = 0; i < sizeof( m_NowKeyState ) / sizeof( bool ); ++i )
	{
		if ( m_NowKeyState[i] == true )
			return true;
	}
	return false;
}
