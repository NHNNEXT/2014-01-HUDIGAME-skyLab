#pragma once
#include "ClientObject.h"

namespace DDWrapper
{
	// 솔직히 이걸 바로 부를 일은 별로 없을 것 같긴 함
	// 그런데 그것이 실제로 일어났습니다
	public ref class GameObject
	{
	public:
		GameObject() : m_pObject( new ClientObject() ) {};
		~GameObject();

		void Release() { m_pObject->Release(); };

		void Render() { m_pObject->Render(); };
		void Update( float dTime ) { m_pObject->Update( dTime ); };

		//const ClientObject* GetParent() { return m_pObject->GetParent(); };
		//const std::list<std::shared_ptr<ClientObject>>& GetChildList() { return m_pObject->GetChildList(); };

		ClientObject* GetPointer() { return m_pObject; }

		void AddChild( ClientObject* object ) { m_pObject->AddChild( object ); };
		void AddChild( DDWrapper::GameObject^ object ) { m_pObject->AddChild( object->GetPointer() ); };
		
		// AddChild는 포인터를 받아야 되는데 C#은 포인터를 못 써서 만든 메소드들
		// 별 거 아니지만 이렇게 쓸려면 Model, Camera, Light가 Object 위에 선언되어 있어야 함
		// 		void AddChild( DDWrapper::GameModel^ object ) { AddChild( object->GetPointer() ); };
		// 		void AddChild( DDWrapper::GameCamera^ object ) { AddChild( object->GetPointer() ); };
		// 		void AddChild( DDWrapper::GameLight^ object ) { AddChild( object->GetPointer() ); };
		void RemoveChild( ClientObject* object ) { m_pObject->RemoveChild( object ); };

		const D3DXMATRIXA16 GetMatrix() { return m_pObject->GetMatrix(); };

		inline const DDVECTOR3 GetPosition() { return m_pObject->GetTransform().GetPosition(); };
		inline const float GetPositionX() { return m_pObject->GetTransform().GetPositionX(); };
		inline const float GetPositionY() { return m_pObject->GetTransform().GetPositionY(); };
		inline const float GetPositionZ() { return m_pObject->GetTransform().GetPositionZ(); };
// 
		inline const DDVECTOR3 GetScale() { return m_pObject->GetTransform().GetScale(); };
		inline const float GetScaleX() { return m_pObject->GetTransform().GetScaleX(); };
		inline const float GetScaleY() { return m_pObject->GetTransform().GetScaleY(); };
		inline const float GetScaleZ() { return m_pObject->GetTransform().GetScaleZ(); };
// 
		inline const DDVECTOR3 GetRotation() { return m_pObject->GetTransform().GetRotation(); };
		inline const float GetRotationX() { return m_pObject->GetTransform().GetRotationX(); };
		inline const float GetRotationY() { return m_pObject->GetTransform().GetRotationY(); };
		inline const float GetRotationZ() { return m_pObject->GetTransform().GetRotationZ(); };
// 
		void IncreasePosition( DDVECTOR3 position ) { return m_pObject->GetTransform().IncreasePosition( position ); };
		void IncreasePositionX( float x ) { return m_pObject->GetTransform().IncreasePositionX( x ); };
		void IncreasePositionY( float y ) { return m_pObject->GetTransform().IncreasePositionY( y ); };
		void IncreasePositionZ( float z ) { return m_pObject->GetTransform().IncreasePositionZ( z ); };
// 
		void IncreaseScale( DDVECTOR3 scale ) { m_pObject->GetTransform().IncreaseScale( scale ); };
		void IncreaseScaleX( float x ) { m_pObject->GetTransform().IncreaseScaleX( x ); };
		void IncreaseScaleY( float y ) { m_pObject->GetTransform().IncreaseScaleY( y ); };
		void IncreaseScaleZ( float z ) { m_pObject->GetTransform().IncreaseScaleZ( z ); };
// 
		void IncreaseRotation( DDVECTOR3 rotation ) { m_pObject->GetTransform().IncreaseRotation( rotation ); };
		void IncreaseRotationX( float x ) { m_pObject->GetTransform().IncreaseRotationX( x ); };
		void IncreaseRotationY( float y ) { m_pObject->GetTransform().IncreaseRotationY( y ); };
		void IncreaseRotationZ( float z ) { m_pObject->GetTransform().IncreaseRotationZ( z ); };
// 
// 		inline const bool IsVisible() { return m_pObject->IsVisible(); };
// 
		void SetPosition( float x, float y, float z ) { m_pObject->GetTransform().SetPosition( x, y, z ); };
		void SetPosition( DDVECTOR3 point ) { m_pObject->GetTransform().SetPosition( point ); };
// 
		void SetScale( float scaleX, float scaleY, float scaleZ ) { m_pObject->GetTransform().SetScale( scaleX, scaleY, scaleZ ); };
		void SetScale( DDVECTOR3 scale ) { m_pObject->GetTransform().SetScale( scale ); };
// 
		void SetRotation( DDVECTOR3 rotation ) { m_pObject->GetTransform().SetRotation( rotation ); };
		void SetRotation( float rotationX, float rotationY, float rotationZ ) { m_pObject->GetTransform().SetRotation( rotationX, rotationY, rotationZ ); };

		void SetVisible( bool visible ) { m_pObject->SetVisible( visible ); };

		// z축 방향 벡터를 월드 좌표계 기준으로 반환
		DDVECTOR3 GetViewDirection() { return m_pObject->GetViewDirection(); };
	protected:
		ClientObject* m_pObject;
	};

}
