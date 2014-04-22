#include "stdafx.h"
#include "Renderer.h"

namespace DDWrapper
{
	////////////////////////////////// Renderer Class //////////////////////////////////	
	// ������
	Renderer::Renderer()
		:m_pDDRenderer( m_pDDRenderer->GetInstance() )
	{

	}

	// �Ҹ���
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