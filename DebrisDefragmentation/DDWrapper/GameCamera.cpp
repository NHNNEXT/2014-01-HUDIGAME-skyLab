#include "stdafx.h"
#include "GameCamera.h"

namespace DDWrapper
{

	GameCamera::GameCamera( float width, float height )
	{
		m_pObject = GameCamera::Create();
		SetAspectRatio( width, height );
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

