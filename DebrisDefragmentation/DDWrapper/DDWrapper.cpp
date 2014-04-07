// 기본 DLL 파일입니다.

#include "stdafx.h"

#include "DDWrapper.h"

namespace DDWrapper
{
	DDRenderer* Renderer::GetInstance()
	{
		return m_pDDRenderer->GetInstance();
	}

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
}
