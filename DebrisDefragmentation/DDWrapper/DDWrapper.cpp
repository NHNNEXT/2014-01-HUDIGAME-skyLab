// �⺻ DLL �����Դϴ�.

#include "stdafx.h"

#include "DDWrapper.h"

namespace DDWrapper
{
	DDRenderer* Renderer::GetInstance()
	{
		return m_pDDRenderer->GetInstance();
	}

	// ������
	Renderer::Renderer()
		:m_pDDRenderer( GetInstance() )
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
}
