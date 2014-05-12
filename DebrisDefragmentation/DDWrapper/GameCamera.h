#pragma once
#include "GameObject.h"

namespace DDWrapper
{

	public ref class GameCamera : GameObject
	{
	public:
		GameCamera(float width, float height);
		~GameCamera();

		const float GetPositionX() { return m_pObject->GetTransform().GetPositionX(); }
		const float GetPositionY() { return m_pObject->GetTransform().GetPositionY(); }
		const float GetPositionZ() { return m_pObject->GetTransform().GetPositionZ(); }
// 
		void SetPosition( float x, float y, float z ) { m_pObject->GetTransform().SetPosition( x, y, z ); };
		
		void SetFollwingObject( GameObject^ obj ) { dynamic_cast<DDCamera*>(m_pObject)->SetFollowingObject( obj->GetPointer() ); }
		void SetAspectRatio( float width, float height ) { dynamic_cast<DDCamera*>( m_pObject )->SetAspectRatio( width, height ); }

		const float GetViewDirectionX() { return m_pObject->GetViewDirection().x; }
		const float GetViewDirectionY() { return m_pObject->GetViewDirection().y; }
		const float GetViewDirectionZ() { return m_pObject->GetViewDirection().z; }

	protected:
		DDCamera* Create() { m_pObject = DDCamera::Create();  return dynamic_cast<DDCamera*>(m_pObject); };
		
	private:

		float WindowsWidth = 0;
		float WindowsHeight = 0;
	};
}
