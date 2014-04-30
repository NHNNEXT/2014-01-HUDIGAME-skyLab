#pragma once
#include "GameObject.h"
#include "DDCamera.h"

namespace DDWrapper
{

	public ref class GameCamera : GameObject
	{
	public:
		GameCamera();
		~GameCamera();

		const float GetPositionX() { return m_pObject->GetPositionX(); }
		const float GetPositionY() { return m_pObject->GetPositionY(); }
		const float GetPositionZ() { return m_pObject->GetPositionZ(); }

		void SetPosition( float x, float y, float z ) { m_pObject->SetPosition( x, y, z ); };

		const float GetViewDirectionX() { return m_pObject->GetViewDirection().x; }
		const float GetViewDirectionY() { return m_pObject->GetViewDirection().y; }
		const float GetViewDirectionZ() { return m_pObject->GetViewDirection().z; }

	protected:
		DDCamera* Create() { return DDCamera::Create(); };
	};
}
