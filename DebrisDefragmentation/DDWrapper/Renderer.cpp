#include "stdafx.h"
#include "Renderer.h"

namespace DDWrapper
{
	////////////////////////////////// Renderer Class //////////////////////////////////	
	// 持失切
	Renderer::Renderer()
		:m_pDDRenderer( m_pDDRenderer->GetInstance() )
	{

	}

	// 社瑚切
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