// �ۼ��� : ������
// ���� ������ : 2014. 04. 14
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
#include "DDPhysics.h"

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

	////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////// Renderer ///////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

	public ref class Renderer
	{
	public:
		Renderer();
		~Renderer();

		DDRenderer* GetInstance();

		bool Init( INT32 hWnd, int Width, int Height ) { return m_pDDRenderer->Init( reinterpret_cast<HWND>( hWnd ), Width, Height ); };
		bool Release() { return m_pDDRenderer->Release(); };

		bool Clear() { return m_pDDRenderer->Clear(); };
		bool BeginDraw() { return m_pDDRenderer->Begin(); };
		bool EndDraw() { return m_pDDRenderer->End(); };

		LPDIRECT3DDEVICE9 GetDevice() { return m_pDDRenderer->GetDevice(); };
		
	protected:
		DDRenderer* m_pDDRenderer;
	};


	////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////// Camera ////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

	public ref class GameCamera
	{
	public:
		GameCamera();
		~GameCamera();

		DDCamera* GetPointer() { return m_pCamera; };

		const float GetPositionX() { return m_pCamera->GetPositionX(); }
		const float GetPositionY() { return m_pCamera->GetPositionY(); }
		const float GetPositionZ() { return m_pCamera->GetPositionZ(); }

		void SetPosition( float x, float y, float z ) { m_pCamera->SetPosition( x, y, z ); };

		const float GetViewDirectionX() { return m_pCamera->GetViewDirection().x; }
		const float GetViewDirectionY() { return m_pCamera->GetViewDirection().y; }
		const float GetViewDirectionZ() { return m_pCamera->GetViewDirection().z; }

	protected:
		DDCamera* Create() { return DDCamera::Create(); };
		DDCamera* m_pCamera;
	};

	////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////// Model /////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

	public ref class GameModel
	{
	public:
		GameModel() : m_pModel( new DDModel() ) {};
		GameModel( System::String^ filepath );
		~GameModel();

		void AddChild( GameCamera^ camera ) { m_pModel->AddChild( camera->GetPointer() ); };

		DDVECTOR3 GetPosition() { return m_pModel->GetPosition(); }
		const float GetPositionX() { return m_pModel->GetPositionX(); }
		const float GetPositionY() { return m_pModel->GetPositionY(); }
		const float GetPositionZ() { return m_pModel->GetPositionZ(); }

		const float GetViewDirectionX() { return m_pModel->GetViewDirection().x; }
		const float GetViewDirectionY() { return m_pModel->GetViewDirection().y; }
		const float GetViewDirectionZ() { return m_pModel->GetViewDirection().z; }

		void SetPosition( DDVECTOR3 position ) { m_pModel->SetPosition( position ); };
		void SetPosition( float x, float y, float z ) { m_pModel->SetPosition( x, y, z ); };

		// wrapping �� m_pModel�� ������ ���� �޼���
		DDModel* GetPointer() { return m_pModel; };

	protected:
		DDModel* m_pModel;
	};

	////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////// Light ////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

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
	
	////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////// Object ////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

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

	////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////// Physics ///////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	// ���� :: ���� �����ο� �ִ� Physics�ʹ� ���� ������ �� ����. ���߿� ���� ������Ʈ�� �и��ؼ� ���� ������ ����
	// ���� :: Physics ���� ����� Ŭ������
	// Framework�� Player�� ���� ������ �ð� ��� ���� �������ֱ� ���� ������ Ŭ����
	// ���� Ŭ���������� DWORD ���� ����� ����� ���� ���� ���� (�����ͷ� ������ ��)
	public class PhysicsData
	{
	public:
		// ���� ���۰� ���� ���� ó��.
		void StartAccelation()
		{
			if ( m_IsAccelerating )
			{
				Update();
			}
			else
			{
				m_StartTime = timeGetTime();
				m_IsAccelerating = true;
			}
		}

		void StopAccelation()
		{
			m_StartTime = 0;
			m_dTime = 0;
			m_IsAccelerating = false;
		}

		// ���� ������ �ƴ����� �˷��ش�.
		bool IsAccelation() { return m_IsAccelerating; }

		// �� ���� �ð��� ��ȯ�Ѵ�.
		DWORD TimeOfAccelation() { return m_dTime; }

	private:
		// ���� �ð��� ������Ʈ�Ѵ�.
		void Update() { m_dTime = timeGetTime() - m_StartTime; }

		DWORD m_dTime = 0.0f;
		DWORD m_StartTime = 0.0f;

		bool m_IsAccelerating = false;
	};

	public ref class GamePhysics
	{
	public:
		GamePhysics() : m_pPhysicsData( new PhysicsData() ) {};
		~GamePhysics() {};
		
		// ���
		void MoveObject( GameModel^ object, float velocityX, float velocityY, float velocityZ, float dt )
		{
			DDVECTOR3 result = object->GetPosition();
			DDVECTOR3 velocity = DDVECTOR3( velocityX, velocityY, velocityZ );
			CalcCurrentPosition( result, velocity, dt );

			object->SetPosition( result );
		}

		// ���
		// ���� : velocity ���� ���������� �����Ƿ� ȣ���� �ʿ��� �Ź� dt��ŭ �����ؾ� �Ѵ�.
		bool AccelObject( GameModel^ object, float velocityX, float velocityY, float velocityZ,
			float accelX, float accelY, float accelZ, float dt )
		{
			m_pPhysicsData->StartAccelation();

			DDVECTOR3 result = object->GetPosition();
			DDVECTOR3 velocity = DDVECTOR3( velocityX, velocityY, velocityZ );
			DDVECTOR3 accel = DDVECTOR3( accelX, accelY, accelZ );
			CalcCurrentPosition( result, velocity, accel, dt );

			object->SetPosition( result );

			if ( m_pPhysicsData->TimeOfAccelation() > 500 )
			{
				m_pPhysicsData->StopAccelation();
				// ���� ��. false�� ������ ȣ���� �ʿ����� ���ӵ� ����� 0���� �����.
				return false;
			}
			else
			{
				// ���� OK
				return true;
			}
		}

		// �ڷ����� �޶� C#���� �ٷ� ������ ����
		// �� ���ĺ��ô�
	private:
		/*
		input : ���� ��ġ, �ӵ�, �ð� ��ȭ��
		output : ������Ʈ�� ���� ��ġ
		���� : ��ӿ�� ��� ���, ���ӵ��� ���� ����� �ʿ��ϸ� �����ε��� �Լ� ����� ��
		*/
		void CalcCurrentPosition( _Inout_ DDVECTOR3& pos, const DDVECTOR3& velocity, float dt )
		{
			DDPhysics::CalcCurrentPosition( &pos, velocity, dt );
		}
		/*
		input : ���� ��ġ, ���� �ӵ�, ���ӵ�, �ð� ��ȭ��
		output : ������Ʈ�� ���� ��ġ, ������Ʈ�� ���� �ӵ�
		���� : ���ӵ��� ���� ��� ��� ���, ��ӿ�� ��� �����ε��� �Լ� ����� ��
		*/
		void CalcCurrentPosition( _Inout_ DDVECTOR3& pos, _Inout_ DDVECTOR3& velocity, const DDVECTOR3& acceleration, float dt )
		{
			DDPhysics::CalcCurrentPosition( &pos, &velocity, acceleration, dt );
		}
		/*
		input : ���� ���Ϳ� ����� ����� ���� �ּ�
		output : ���� ������ ��� ����
		*/
		void GetNormalVector( _In_ DDVECTOR3* srcVec, _Out_ DDVECTOR3* normalVec )
		{
			DDPhysics::GetNormalVector( srcVec, normalVec );
		}

		PhysicsData* m_pPhysicsData;
	};

}
