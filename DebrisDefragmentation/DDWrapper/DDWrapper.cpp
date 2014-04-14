// 기본 DLL 파일입니다.

#include "stdafx.h"

#include "DDWrapper.h"

namespace DDWrapper
{	
	//////////////////////////////////////////// Renderer Class //////////////////////////////	
	// 생성자
	Renderer::Renderer()
		:m_pDDRenderer( GetInstance() )
	{

	}

	// 소멸자
	Renderer::~Renderer()
	{
		if ( m_pDDRenderer != nullptr )
		{
			m_pDDRenderer->Release();
			m_pDDRenderer = nullptr;
		}
	}

// 	DDRenderer* Renderer::GetInstance()
// 	{
// 		return m_pDDRenderer->GetInstance();
// 	}
// 
// 
// 	bool Renderer::Init( INT32 hWnd, int Width, int Height )
// 	{
// 		return m_pDDRenderer->GetInstance()->Init( (HWND)hWnd, Width, Height );
// 	}
// 
// 
// 	bool Renderer::Release()
// 	{
// 		return m_pDDRenderer->GetInstance()->Release();
// 	}
// 
// 	bool Renderer::Clear()
// 	{
// 		return m_pDDRenderer->GetInstance()->Clear();
// 	}
// 
// 	bool Renderer::BeginDraw()
// 	{
// 		return m_pDDRenderer->GetInstance()->Begin();
// 	}
// 
// 	bool Renderer::EndDraw()
// 	{
// 		return m_pDDRenderer->GetInstance()->End();
// 	}



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
		m_pCamera = GameCamera::Create();
	}

	GameCamera::~GameCamera()
	{
		if ( nullptr != m_pCamera )
		{
			m_pCamera->Release();
			delete m_pCamera;
		}

		m_pCamera = nullptr;
	}

	////////////////////////////////// DD Model Class //////////////////////////////

	GameModel::GameModel( System::String^ filepath, Renderer^ renderer )
	{
		pin_ptr<const wchar_t> str = PtrToStringChars( filepath );
		//const wchar_t* str = L"tiger.x";
		//m_pModel = new DDModel( const_cast<wchar_t*>(str) );
		//wchar_t* str = L"tiger.x";

		m_pModel = DDModel::Create( const_cast<wchar_t*>( str ), renderer->GetInstance()->GetDevice() );
	}

	GameModel::~GameModel()
	{
		if ( nullptr != m_pModel )
		{
			m_pModel->Release();
			delete m_pModel;
		}

		m_pModel = nullptr;
	}
	
	////////////////////////////////// DD Light Class //////////////////////////////


	GameLight::GameLight()
	{
		m_pLight = DDLight::Create();
	}

	GameLight::~GameLight()
	{
		if ( nullptr != m_pLight )
		{
			m_pLight->Release();
			delete m_pLight;
		}
		m_pLight = nullptr;
	}

}	
