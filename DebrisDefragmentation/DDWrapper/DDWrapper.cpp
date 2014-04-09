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

	DDRenderer* Renderer::GetInstance()
	{
		return m_pDDRenderer->GetInstance();
	}


	bool Renderer::Init( INT32 hWnd, int Width, int Height )
	{
		return m_pDDRenderer->GetInstance()->Init( (HWND)hWnd, Width, Height );
	}


	bool Renderer::Release()
	{
		return m_pDDRenderer->GetInstance()->Release();
	}

	bool Renderer::Clear()
	{
		return m_pDDRenderer->GetInstance()->Clear();
	}

	bool Renderer::BeginDraw()
	{
		return m_pDDRenderer->GetInstance()->Begin();
	}

	bool Renderer::EndDraw()
	{
		return m_pDDRenderer->GetInstance()->End();
	}



	////////////////////////////////// DD Object Class //////////////////////////////



	Object::~Object()
	{
		if ( nullptr != m_pObject )
		{
			m_pObject->Release();
		}

		m_pObject = nullptr;
	}

}
