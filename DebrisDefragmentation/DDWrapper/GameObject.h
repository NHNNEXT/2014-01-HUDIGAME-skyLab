#pragma once
#include "DDObject.h"

namespace DDWrapper
{
	// 솔직히 이걸 바로 부를 일은 별로 없을 것 같긴 함
	// 그런데 그것이 실제로 일어났습니다
	public ref class GameObject
	{
	public:
		GameObject() : m_pObject( DDObject::Create() ) {};
		~GameObject();

		void Release() { m_pObject->Release(); };

		void Render() { m_pObject->Render(); };
		void Update( float dTime ) { m_pObject->Update( dTime ); };

		const DDObject* GetParent() { return m_pObject->GetParent(); };
		const std::list<std::shared_ptr<DDObject>>& GetChildList() { return m_pObject->GetChildList(); };

		DDObject* GetPointer() { return m_pObject; }

		void AddChild( DDObject* object ) { m_pObject->AddChild( object ); };
		void AddChild( DDWrapper::GameObject^ object ) { m_pObject->AddChild( object->GetPointer() ); };
		// AddChild는 포인터를 받아야 되는데 C#은 포인터를 못 써서 만든 메소드들
		// 별 거 아니지만 이렇게 쓸려면 Model, Camera, Light가 Object 위에 선언되어 있어야 함
		// 		void AddChild( DDWrapper::GameModel^ object ) { AddChild( object->GetPointer() ); };
		// 		void AddChild( DDWrapper::GameCamera^ object ) { AddChild( object->GetPointer() ); };
		// 		void AddChild( DDWrapper::GameLight^ object ) { AddChild( object->GetPointer() ); };
		void RemoveChild( DDObject* object ) { m_pObject->RemoveChild( object ); };

		const D3DXMATRIXA16 GetMatrix() { return m_pObject->GetMatrix(); };

		inline const DDVECTOR3 GetPosition() { return m_pObject->GetPosition(); };
		inline const float GetPositionX() { return m_pObject->GetPositionX(); };
		inline const float GetPositionY() { return m_pObject->GetPositionY(); };
		inline const float GetPositionZ() { return m_pObject->GetPositionZ(); };

		inline const DDVECTOR3 GetScale() { return m_pObject->GetScale(); };
		inline const float GetScaleX() { return m_pObject->GetScaleX(); };
		inline const float GetScaleY() { return m_pObject->GetScaleY(); };
		inline const float GetScaleZ() { return m_pObject->GetScaleZ(); };

		inline const DDVECTOR3 GetRotation() { return m_pObject->GetRotation(); };
		inline const float GetRotationX() { return m_pObject->GetRotationX(); };
		inline const float GetRotationY() { return m_pObject->GetRotationY(); };
		inline const float GetRotationZ() { return m_pObject->GetRotationZ(); };

		void IncreasePosition( DDVECTOR3 position ) { return m_pObject->IncreasePosition( position ); };
		void IncreasePositionX( float x ) { return m_pObject->IncreasePositionX( x ); };
		void IncreasePositionY( float y ) { return m_pObject->IncreasePositionY( y ); };
		void IncreasePositionZ( float z ) { return m_pObject->IncreasePositionZ( z ); };

		void IncreaseScale( DDVECTOR3 scale ) { m_pObject->IncreaseScale( scale ); };
		void IncreaseScaleX( float x ) { m_pObject->IncreaseScaleX( x ); };
		void IncreaseScaleY( float y ) { m_pObject->IncreaseScaleY( y ); };
		void IncreaseScaleZ( float z ) { m_pObject->IncreaseScaleZ( z ); };

		void IncreaseRotation( DDVECTOR3 rotation ) { m_pObject->IncreaseRotation( rotation ); };
		void IncreaseRotationX( float x ) { m_pObject->IncreaseRotationX( x ); };
		void IncreaseRotationY( float y ) { m_pObject->IncreaseRotationY( y ); };
		void IncreaseRotationZ( float z ) { m_pObject->IncreaseRotationZ( z ); };

		inline const bool IsVisible() { return m_pObject->IsVisible(); };

		void SetPosition( float x, float y, float z ) { m_pObject->SetPosition( x, y, z ); };
		void SetPosition( DDVECTOR3 point ) { m_pObject->SetPosition( point ); };

		void SetScale( float scaleX, float scaleY, float scaleZ ) { m_pObject->SetScale( scaleX, scaleY, scaleZ ); };
		void SetScale( DDVECTOR3 scale ) { m_pObject->SetScale( scale ); };

		void SetRotation( DDVECTOR3 rotation ) { m_pObject->SetRotation( rotation ); };
		void SetRotation( float rotationX, float rotationY, float rotationZ ) { m_pObject->SetRotation( rotationX, rotationY, rotationZ ); };

		void SetVisible( bool visible ) { m_pObject->SetVisible( visible ); };

		// z축 방향 벡터를 월드 좌표계 기준으로 반환
		DDVECTOR3 GetViewDirection() { return m_pObject->GetViewDirection(); };
	protected:
		DDObject* m_pObject;
	};

}
