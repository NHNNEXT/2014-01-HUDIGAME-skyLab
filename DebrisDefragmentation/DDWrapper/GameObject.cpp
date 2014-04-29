#include "stdafx.h"
#include "GameObject.h"

namespace DDWrapper
{

	GameObject::~GameObject()
	{
		if ( nullptr != m_pObject )
		{
			m_pObject->Release();
			delete m_pObject;
		}

		m_pObject = nullptr;
	}

}