#include "stdafx.h"
#include "DDObject.h"
#include "DDRenderer.h"

DDObject::DDObject() :
m_pParent( nullptr ),
m_Position( .0f, .0f, .0f ),
m_Rotation( .0f, .0f, .0f ),
m_Scale( 1.0f, 1.0f, 1.0f ),
m_Visible( true )
{
	
}


DDObject::~DDObject()
{
}

// �ۼ��� : �輺ȯ
// �ۼ��� : 14.04.06
// ���� : object�� affine��ȯ �� �ڽ� ��� render
void DDObject::Render()
{
	if ( m_Visible == false ) return;
		
	AffineTransfrom();
	RenderChildNodes();
}

void DDObject::Update( float dTime )
{
	if ( m_Visible == false ) return;
	
	UpdateChildNodes( dTime );
}

void DDObject::AffineTransfrom()
{
	D3DXQUATERNION	qRotation;
	DDRenderer* renderer = DDRenderer::GetInstance();

	D3DXMatrixIdentity( &m_Matrix );

	// rotation���� ���ʹϾ� ����, yaw ptich roll �� y, x, z ������
	D3DXQuaternionRotationYawPitchRoll( &qRotation, m_Rotation.y, m_Rotation.x, m_Rotation.z );
	
	// matrix�� affine��ȯ�� ����� ���·� ��ȯ	
	D3DXMatrixTransformation( &m_Matrix, NULL, NULL, &m_Scale, &m_Position, &qRotation, &m_Position );

	// �ڽ��� ������ ��ȯ ����
	if ( FAILED( renderer->GetDevice()->SetTransform( D3DTS_WORLD, &m_Matrix ) ) )
	{
		// error 
		return;
	}

	// �θ��� ������ ��ȯ�� ����
	if ( nullptr != m_pParent )
	{
		if ( FAILED( renderer->GetDevice()->MultiplyTransform( D3DTS_WORLD, &m_pParent->GetMatrix() ) ) )
		{
			// error
			return;
		}
	}
}

void DDObject::RenderChildNodes()
{
	for ( const auto& child : m_ChildList )
	{
		child->Render();
	}
}

void DDObject::UpdateChildNodes( float dTime )
{
	for ( const auto& child : m_ChildList )
	{
		child->Update( dTime );
	}
}

void DDObject::AddChild( DDObject* object )
{
	object->SetParent( this );
	m_ChildList.push_back( object );
}

void DDObject::RemoveChild( DDObject* object )
{
	for ( auto& iter = m_ChildList.begin(); iter != m_ChildList.end(); iter++ )
	{
		if ( ( *iter ) == object )
		{
			SafeDelete( *iter );
			m_ChildList.erase( iter );
			break;
		}
	}
}
