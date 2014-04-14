// �⺻ DLL �����Դϴ�.

#include "stdafx.h"

#include "DDWrapper.h"

namespace DDWrapper
{	
	//////////////////////////////////////////// Renderer Class //////////////////////////////	
	// ������
	Renderer::Renderer()
		:m_pDDRenderer( m_pDDRenderer->GetInstance() )
	{

	}

	// �Ҹ���
	Renderer::~Renderer()
	{
		if ( m_pDDRenderer != nullptr )
		{
			m_pDDRenderer->Release();
			m_pDDRenderer = nullptr;
		}
	}

	DDRenderer* Renderer::GetInstance()
	{
		return m_pDDRenderer->GetInstance();
	}

	////////////////////////////////// DD Object Class //////////////////////////////

	GameObject::~GameObject()
	{
		if ( nullptr != m_pObject )
		{
			m_pObject->Release();
			delete m_pObject;
		}
		
		m_pObject = nullptr;
	}

	////////////////////////////////// DD Camera Class //////////////////////////////


	GameCamera::GameCamera()
	{
		m_pCamera = GameCamera::Create();
	}

	GameCamera::~GameCamera()
	{
		if ( nullptr != m_pCamera )
		{
			m_pCamera->Release();
			delete m_pCamera;
		}

		m_pCamera = nullptr;
	}

	////////////////////////////////// DD Model Class //////////////////////////////

	GameModel::GameModel( System::String^ filepath, Renderer^ renderer )
	{
		pin_ptr<const wchar_t> str = PtrToStringChars( filepath );
		//const wchar_t* str = L"tiger.x";
		//m_pModel = new DDModel( const_cast<wchar_t*>(str) );
		//wchar_t* str = L"tiger.x";

		m_pModel = DDModel::Create( const_cast<wchar_t*>(str), renderer->GetDevice() );
	}

	GameModel::~GameModel()
	{
		if ( nullptr != m_pModel )
		{
			m_pModel->Release();
			delete m_pModel;
		}

		m_pModel = nullptr;
	}

	////////////////////////////////// DD Light Class //////////////////////////////


	GameLight::GameLight()
	{
		m_pLight = DDLight::Create();
	}

	GameLight::~GameLight()
	{
		if ( nullptr != m_pLight )
		{
			m_pLight->Release();
			delete m_pLight;
		}
		m_pLight = nullptr;
	}

}
