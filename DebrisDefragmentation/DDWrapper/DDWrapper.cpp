// 기본 DLL 파일입니다.

#include "stdafx.h"

#include "DDWrapper.h"

namespace DDWrapper
{	
	////////////////////////////////// DD Object Class //////////////////////////////

	GameObject::~GameObject()
	{
		if ( nullptr != m_pObject )
		{
			m_pObject->Release();
			delete m_pObject;
		}
		
		m_pObject = nullptr;
	}

	////////////////////////////////// DD Camera Class //////////////////////////////


	GameCamera::GameCamera()
	{
		m_pObject = GameCamera::Create();
	}

	GameCamera::~GameCamera()
	{
		if ( nullptr != m_pObject )
		{
			m_pObject->Release();
			delete m_pObject;
		}

		m_pObject = nullptr;
	}

	////////////////////////////////// DD Model Class //////////////////////////////

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

	////////////////////////////////// DD Light Class //////////////////////////////


	GameLight::GameLight()
	{
		m_pObject = DDLight::Create();
	}

	GameLight::~GameLight()
	{
		if ( nullptr != m_pObject )
		{
			m_pObject->Release();
			delete m_pObject;
		}
		m_pObject = nullptr;
	}

}
