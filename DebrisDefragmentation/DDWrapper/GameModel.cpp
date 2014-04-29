#include "stdafx.h"
#include "GameModel.h"
#include <vcclr.h>

namespace DDWrapper
{

	GameModel::GameModel( System::String^ filepath )
	{
		pin_ptr<const wchar_t> str = PtrToStringChars( filepath );
		//const wchar_t* str = L"tiger.x";
		//m_pModel = new DDModel( const_cast<wchar_t*>(str) );
		//wchar_t* str = L"tiger.x";

		//m_pModel = DDModel::Create( const_cast<wchar_t*>(str), renderer->GetDevice() );
		m_pObject = DDModel::Create( const_cast<wchar_t*>( str ) );
	}

	GameModel::~GameModel()
	{
		if ( nullptr != m_pObject )
		{
			m_pObject->Release();
			delete m_pObject;
		}

		m_pObject = nullptr;
	}

}