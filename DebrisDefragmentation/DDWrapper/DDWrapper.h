// 작성자 : 문진상
// 최종 수정일 : 2014. 04. 14
// 기능 : C# 툴에서 DDFramework를 쓸 수 있게 감싸놓은 클래스

// DDWrapper.h
// warning!! 만약 lib가 출력되는 폴더가 바뀌면 아래 옵션도 바꿔야 한다
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

ref class GameObject;

namespace DDWrapper {
	// DDWrapper 안에서 사용할 유틸리티들
	public ref class Utilities
	{
	public:
		
	};

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
		GameModel( System::String^ filepath, Renderer^ renderer );
		GameModel( wchar_t* filePath ) : m_pModel( new DDModel( filePath ) ) {}
		~GameModel();

		void AddChild( GameCamera^ camera ) { m_pModel->AddChild( camera->GetPointer() ); };

		DDVECTOR3 GetPosition() { return m_pModel->GetPosition(); }
		const float GetPositionX() { return m_pModel->GetPositionX(); }
		const float GetPositionY() { return m_pModel->GetPositionY(); }
		const float GetPositionZ() { return m_pModel->GetPositionZ(); }

		void SetPosition( DDVECTOR3 position ) { m_pModel->SetPosition( position ); };
		void SetPosition( float x, float y, float z ) { m_pModel->SetPosition( x, y, z ); };

		// wrapping 된 m_pModel을 꺼내기 위한 메서드
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

	
	public ref class GamePhysics
	{
	public:
		GamePhysics() {};
		~GamePhysics() {};

		void Accelation(GameObject^ object, float dt)
		{

		}

		// 자료형이 달라서 C#에서 바로 쓰지는 못함
		// 잘 고쳐봅시다
	private:
		/*
		input : 현재 위치, 속도, 시간 변화량
		output : 업데이트된 현재 위치
		주의 : 등속운동인 경우 사용, 가속도에 의한 계산이 필요하면 오버로딩된 함수 사용할 것
		*/
		void CalcCurrentPosition( _Inout_ DDVECTOR3* pos, const DDVECTOR3 &velocity, float dt )
		{
			DDPhysics::CalcCurrentPosition( pos, velocity, dt );
		}

		/*
		input : 현재 위치, 현재 속도, 가속도, 시간 변화량
		output : 업데이트된 현재 위치, 업데이트된 현재 속도
		주의 : 가속도에 의한 운동인 경우 사용, 등속운동의 경우 오버로딩된 함수 사용할 것
		*/
		void CalcCurrentPosition( _Inout_ DDVECTOR3* pos, _Inout_ DDVECTOR3* velocity, const DDVECTOR3 &acceleration, float dt )
		{
			DDPhysics::CalcCurrentPosition( pos, velocity, acceleration, dt );
		}
		/*
		input : 원본 벡터와 결과가 저장될 벡터 주소
		output : 원본 벡터의 노멀 벡터
		*/
		void GetNormalVector( _In_ DDVECTOR3* srcVec, _Out_ DDVECTOR3* normalVec )
		{
			DDPhysics::GetNormalVector( srcVec, normalVec );
		}

	};
	
	////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////// Object ////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

	// 솔직히 이걸 바로 부를 일은 별로 없을 것 같긴 함
	// 그런데 그것이 실제로 일어났습니다
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
		// AddChild는 포인터를 받아야 되는데 C#은 포인터를 못 써서 만든 메소드들
		// 별 거 아니지만 이렇게 쓸려면 Model, Camera, Light가 Object 위에 선언되어 있어야 함
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
		
		// z축 방향 벡터를 월드 좌표계 기준으로 반환
		DDVECTOR3 GetViewDirection() { return m_pObject->GetViewDirection(); };
	protected:
		DDObject* m_pObject;
	};
}
