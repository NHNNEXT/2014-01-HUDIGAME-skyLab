#pragma once
#include "GameObject.h"
#include "DDCamera.h"

namespace DDWrapper
{

	public ref class GameCamera : GameObject
	{
	public:
		GameCamera(float width, float height);
		~GameCamera();

		const float GetPositionX() { return m_pObject->GetPositionX(); }
		const float GetPositionY() { return m_pObject->GetPositionY(); }
		const float GetPositionZ() { return m_pObject->GetPositionZ(); }

		void SetPosition( float x, float y, float z ) { m_pObject->SetPosition( x, y, z ); };
		// 왜 static_cast냐면 dynamic_cast는 캐스팅이 안 될 수도 있기 때문입니다 물론 static_cast 쓰면 더 위험
		// void Render() { static_cast<DDCamera*>(m_pObject)->Render(); };
		void SetFollwingObject( GameObject^ obj ) { dynamic_cast<DDCamera*>( m_pObject )->SetFollowingObject( obj->GetPointer() ); }

		void SetAspectRatio( float width, float height ) { dynamic_cast<DDCamera*>( m_pObject )->SetAspectRatio( width, height ); }

		const float GetViewDirectionX() { return m_pObject->GetViewDirection().x; }
		const float GetViewDirectionY() { return m_pObject->GetViewDirection().y; }
		const float GetViewDirectionZ() { return m_pObject->GetViewDirection().z; }

	protected:
		DDCamera* Create() { m_pObject = DDCamera::Create();  return dynamic_cast<DDCamera*>(m_pObject); };
	};
}
