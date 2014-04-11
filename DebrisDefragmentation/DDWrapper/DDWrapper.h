
// DDWrapper.h
// warning!! 만약 lib가 출력되는 폴더가 바뀌면 아래 옵션도 바꿔야 한다
#include "../DDFramework/DDRenderer.h"
#include "../DDFramework/DDObject.h"
#include "../DDFramework//DDModel.h"
#include "../DDFramework//DDCamera.h"
#pragma comment( lib, "../Debug/DDFramework.lib")

using namespace System;

namespace DDWrapper {
	// Wrapper 내부에 구현된 클래스들의 기본 구조
	/*
		public ref class 클래스 이름
		{
		public:
			함수들();

		private:
			DD프레임워크 클래스* m_pClass;
			private함수들();
		}
	
	저 private 안에 들어있는 n_pClass 멤버 변수를 이용해서 public 함수들()의 구현을
	하고 있는 모습입니다.
	
	참 쉽죠???
	
	*/

	public ref class Renderer
	{
	public:
		Renderer();
		~Renderer();

		bool Init( INT32 hWnd, int Width, int Height );
		bool Release();

		bool Clear();
		bool BeginDraw();
		bool EndDraw();

	protected:
		DDRenderer* GetInstance();
		DDRenderer* m_pDDRenderer;
	};

	public ref class GameObject
	{
		GameObject() :m_pObject( new DDObject() ) {};
		~GameObject();

		void Release() { m_pObject->Release(); };

		void Render() { m_pObject->Render(); };
		void Update( float dTime ) { m_pObject->Update( dTime );  };

		const DDObject* GetParent() { return m_pObject->GetParent(); };
		const std::list<std::shared_ptr<DDObject>>& GetChildList() { return m_pObject->GetChildList(); };
		
		void AddChild( DDObject* object ) { m_pObject->AddChild( object ); };
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
		void SetRotation( float rotationX, float rotationY, float rotationZ ) { m_pObject->SetRotation( rotationX, rotationY, rotationZ );  };

		void SetVisible( bool visible ) { m_pObject->SetVisible( visible ); };
		
		// z축 방향 벡터를 월드 좌표계 기준으로 반환
		DDVECTOR3 GetViewDirection() { return m_pObject->GetViewDirection(); };
	protected:
		DDObject* m_pObject;
	};

	public ref class GameModel
	{
	public:
		GameModel() : m_pModel(new DDModel()) {};
		GameModel( wchar_t* filepath ) : m_pModel( new DDModel( filepath )){};
		~GameModel();
	
	protected:
		DDModel* m_pModel;
		
	};

	public ref class GameCamera
	{
	public:
		GameCamera() :m_pCamera( m_pCamera->Create() ) {};
		~GameCamera();
	protected:
		DDCamera* m_pCamera;
	};
}
