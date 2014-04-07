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

// 작성자 : 김성환
// 작성일 : 14.04.06
// 내용 : object의 affine변환 및 자식 노드 render
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

	// rotation에서 쿼터니언 생성, yaw ptich roll 은 y, x, z 순서임
	D3DXQuaternionRotationYawPitchRoll( &qRotation, m_Rotation.y, m_Rotation.x, m_Rotation.z );
	
	// matrix를 affine변환이 적용된 형태로 변환	
	D3DXMatrixTransformation( &m_Matrix, NULL, NULL, &m_Scale, &m_Position, &qRotation, &m_Position );

	// 자신의 어파인 변환 적용
	if ( FAILED( renderer->GetDevice()->SetTransform( D3DTS_WORLD, &m_Matrix ) ) )
	{
		// error 
		return;
	}

	// 부모의 어파인 변환을 적용
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
