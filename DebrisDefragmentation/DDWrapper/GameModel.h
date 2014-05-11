#pragma once
#include "GameObject.h"
#include "DDModel.h"
#include "GameCamera.h"


namespace DDWrapper
{

	public ref class GameModel : public GameObject
	{
	public:
		GameModel() { m_pObject = new DDModel(); };
		GameModel( System::String^ filepath );
		~GameModel();

		void AddChild( GameCamera^ camera ) { m_pObject->AddChild( camera->GetPointer() ); };

		DDVECTOR3 GetPosition() { return m_pObject->GetTransform().GetPosition(); }
		const float GetPositionX() { return m_pObject->GetTransform().GetPositionX(); }
		const float GetPositionY() { return m_pObject->GetTransform().GetPositionY(); }
		const float GetPositionZ() { return m_pObject->GetTransform().GetPositionZ(); }

		const float GetViewDirectionX() { return m_pObject->GetViewDirection().x; }
		const float GetViewDirectionY() { return m_pObject->GetViewDirection().y; }
		const float GetViewDirectionZ() { return m_pObject->GetViewDirection().z; }

		void SetPosition( DDVECTOR3 position ) { m_pObject->GetTransform().SetPosition( position ); };
		void SetPosition( float x, float y, float z ) { m_pObject->GetTransform().SetPosition( x, y, z ); };

		void SetScale( float scale ) { m_pObject->GetTransform().SetScale( DDVECTOR3( scale, scale, scale ) ); }

	};

}