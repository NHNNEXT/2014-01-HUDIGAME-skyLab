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

		DDVECTOR3 GetPosition() { return m_pObject->GetPosition(); }
		const float GetPositionX() { return m_pObject->GetPositionX(); }
		const float GetPositionY() { return m_pObject->GetPositionY(); }
		const float GetPositionZ() { return m_pObject->GetPositionZ(); }

		const float GetViewDirectionX() { return m_pObject->GetViewDirection().x; }
		const float GetViewDirectionY() { return m_pObject->GetViewDirection().y; }
		const float GetViewDirectionZ() { return m_pObject->GetViewDirection().z; }

		void SetPosition( DDVECTOR3 position ) { m_pObject->SetPosition( position ); };
		void SetPosition( float x, float y, float z ) { m_pObject->SetPosition( x, y, z ); };

		void SetScale( float scale ) { m_pObject->SetScale( DDVECTOR3( scale, scale, scale ) ); }

	};

}