#include "stdafx.h"
#include "GameCamera.h"

namespace DDWrapper
{

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
}

