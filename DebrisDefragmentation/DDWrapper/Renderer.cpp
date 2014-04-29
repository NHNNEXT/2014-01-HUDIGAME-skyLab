#include "stdafx.h"
#include "Renderer.h"

namespace DDWrapper
{
	////////////////////////////////// Renderer Class //////////////////////////////////	
	// 생성자
	Renderer::Renderer()
		:m_pDDRenderer( m_pDDRenderer->GetInstance() )
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
}