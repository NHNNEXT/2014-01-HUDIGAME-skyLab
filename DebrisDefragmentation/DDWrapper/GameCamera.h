#pragma once
#include "GameObject.h"

namespace DDWrapper
{

	public ref class GameCamera : GameObject
	{
	public:
		GameCamera(float width, float height);
		~GameCamera();

// 		const float GetPositionX() { return m_pObject->GetPositionX(); }
// 		const float GetPositionY() { return m_pObject->GetPositionY(); }
// 		const float GetPositionZ() { return m_pObject->GetPositionZ(); }
// 
// 		void SetPosition( float x, float y, float z ) { m_pObject->SetPosition( x, y, z ); };
		
		// 조심해!! 헬게이트 ㅠㅠ
		//void SetFollwingObject( GameObject^ obj ) { m_pObject->SetFollowingObject( obj->GetPointer() ); }
		//void SetAspectRatio( float width, float height ) { m_pObject->SetAspectRatio( width, height ); }

		const float GetViewDirectionX() { return m_pObject->GetViewDirection().x; }
		const float GetViewDirectionY() { return m_pObject->GetViewDirection().y; }
		const float GetViewDirectionZ() { return m_pObject->GetViewDirection().z; }

	protected:
		ClientObject* Create() { m_pObject = new ClientObject();  return m_pObject; };
		
	private:

		float WindowsWidth = 0;
		float WindowsHeight = 0;
	};
}
