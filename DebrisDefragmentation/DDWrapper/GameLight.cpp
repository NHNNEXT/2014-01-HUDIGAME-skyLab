#include "stdafx.h"
#include "GameLight.h"

namespace DDWrapper
{

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
