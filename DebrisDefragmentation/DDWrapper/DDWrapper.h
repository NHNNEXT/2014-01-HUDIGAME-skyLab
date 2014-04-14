// �ۼ��� : ������
// ���� ������ : 2014. 04. 13
// ��� : C# ������ DDFramework�� �� �� �ְ� ���γ��� Ŭ����

// DDWrapper.h
// warning!! ���� lib�� ��µǴ� ������ �ٲ�� �Ʒ� �ɼǵ� �ٲ�� �Ѵ�
#include "DDRenderer.h"
#include "DDObject.h"
#include "DDModel.h"
#include "DDCamera.h"
#include "DDLight.h"
#pragma comment( lib, "../Debug/DDFramework.lib")

#include <vcclr.h>

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DDWrapper {
	// DDWrapper �ȿ��� ����� ��ƿ��Ƽ��
	public ref class Utilities
	{
	public:
		
	};

	// Wrapper ���ο� ������ Ŭ�������� �⺻ ����
	/*
		public ref class Ŭ���� �̸�
		{
		public:
			�Լ���();

		private:
			DD�����ӿ�ũ Ŭ����* m_pClass;
			private�Լ���();
		}
	
	�� private �ȿ� ����ִ� n_pClass ��� ������ �̿��ؼ� public �Լ���()�� ������
	�ϰ� �ִ� ����Դϴ�.
	
	�� ����???
	
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

		DDRenderer* GetInstance();
	protected:
		DDRenderer* m_pDDRenderer;
	};

	public ref class GameCamera
	{
	public:
		GameCamera();
		~GameCamera();

		DDCamera* GetPointer() { return m_pCamera; };

	protected:
		DDCamera* Create() { return DDCamera::Create(); };
		DDCamera* m_pCamera;
	};

	public ref class GameModel
	{
	public:
		GameModel() : m_pModel( new DDModel() ) {};
		GameModel( System::String^ filepath, Renderer^ renderer );
		GameModel( wchar_t* filePath ) : m_pModel( new DDModel( filePath ) ) {}
		~GameModel();

		void AddChild( GameCamera^ camera ) { m_pModel->AddChild( camera->GetPointer() ); };

		// wrapping �� m_pModel�� ������ ���� �޼���
		DDModel* GetPointer() { return m_pModel; };

	protected:
		DDModel* m_pModel;
	};

	public ref class GameLight
	{
	public:
		GameLight();
		~GameLight();

		DDLight* GetPointer() { return m_pLight; };

	protected:
		DDLight* Create() { return DDLight::Create(); };
		DDLight* m_pLight;
	};

	// ������ �̰� �ٷ� �θ� ���� ���� ���� �� ���� ��
	// �׷��� �װ��� ������ �Ͼ���ϴ�
	public ref class GameObject
	{
	public:
		GameObject() : m_pObject( new DDObject() ) {};
		~GameObject();

		void Release() { m_pObject->Release(); };

		void Render() { m_pObject->Render(); };
		void Update( float dTime ) { m_pObject->Update( dTime );  };

		const DDObject* GetParent() { return m_pObject->GetParent(); };
		const std::list<std::shared_ptr<DDObject>>& GetChildList() { return m_pObject->GetChildList(); };
		
		void AddChild( DDObject* object ) { m_pObject->AddChild( object ); };
		// AddChild�� �����͸� �޾ƾ� �Ǵµ� C#�� �����͸� �� �Ἥ ���� �޼ҵ��
		// �� �� �ƴ����� �̷��� ������ Model, Camera, Light�� Object ���� ����Ǿ� �־�� ��
		void AddChild( DDWrapper::GameModel^ object ) { AddChild( object->GetPointer() ); };
		void AddChild( DDWrapper::GameCamera^ object ) { AddChild( object->GetPointer() ); };
		void AddChild( DDWrapper::GameLight^ object ) { AddChild( object->GetPointer() ); };
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
		
		// z�� ���� ���͸� ���� ��ǥ�� �������� ��ȯ
		DDVECTOR3 GetViewDirection() { return m_pObject->GetViewDirection(); };
	protected:
		DDObject* m_pObject;
	};

}
