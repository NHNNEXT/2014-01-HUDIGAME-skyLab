#include "stdafx.h"
#include "DDObject.h"
#include "DDRenderer.h"
#include "DDApplication.h"

DDObject::DDObject() 
{
	D3DXMatrixIdentity( &m_Matrix );
}

DDObject::~DDObject()
{
	// Release();
}

void DDObject::Release( )
{
}

// 작성일 : 14.04.06
// 내용 : object의 affine변환 및 자식 노드 render
void DDObject::Render()
{
	if ( m_VisibleFlag == false ) return;
		
	AffineTransfrom();
	RenderItSelf();
	RenderChildNodes();
}

void DDObject::Update( float dTime )
{
	if ( m_UpdatableFlag == false ) return;
	
	UpdateItSelf( dTime );
	UpdateChildNodes( dTime );
}

void DDObject::AffineTransfrom()
{	
	// 부모의 좌표계에다 내 변환된 좌표계를 누적 시킨다!
	// 부모의 어파인 변환을 적용
	if ( nullptr != m_pParent )
	{
		D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &m_pParent->GetMatrix() );
	}

	// 자신+부모의 어파인 변환을 월드좌표계에 적용
	if ( FAILED( DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_WORLD, &m_Matrix ) ) )
	{
		// error 
		return;
	}
}

DDVECTOR3 DDObject::GetViewDirection( ) const
{
	return DDVECTOR3( m_Matrix._31, m_Matrix._32, m_Matrix._33 );
}

DDVECTOR3 DDObject::GetAxisX()
{
	return DDVECTOR3( m_Matrix._11, m_Matrix._12, m_Matrix._13 );
}

void DDObject::RenderChildNodes()
{
	for ( const auto& child : m_NormalChildList )
	{
		child->Render();
	}
	
	for ( const auto& child : m_AhphaChildList )
	{
		child->Render();
	}
}

void DDObject::UpdateChildNodes( float dTime )
{
	for ( const auto& child : m_NormalChildList )
	{
		child->Update( dTime );
	}

	for ( const auto& child : m_AhphaChildList )
	{
		child->Update( dTime );
	}
}

void DDObject::AddChild( DDObject* object, int alphaIndex)
{
	auto deleter = DeleteAlignedClass;
	std::shared_ptr<DDObject> object_ptr( object, deleter );
	object->SetParent( this );
	
	if ( 0 != alphaIndex )
	{
		object_ptr->SetAlphaIndex( alphaIndex );
		m_AhphaChildList.push_back( object_ptr );
		m_AhphaChildList.sort( []( std::shared_ptr<DDObject> a, std::shared_ptr<DDObject> b ) -> bool {
			return ( a->GetAlphaIndex() < b->GetAlphaIndex() ) ? true : false; } );		
		return ;	
	}
	m_NormalChildList.push_back( object_ptr );
	
}

void DDObject::RemoveChild( DDObject* object )
{
	// 일반 리스트에서 검색
	for ( auto& iter = m_NormalChildList.begin(); iter != m_NormalChildList.end(); iter++ )
	{
		if ( ( *iter ).get() == object )
		{
			//( *iter )->Release();
			//SafeDelete( *iter );
			m_NormalChildList.erase( iter );
			break;
		}
	}
	// alpha값이 있는 list도 검색
	for ( const auto& iter : m_AhphaChildList )
	{
		if ( iter.get() == object )
		{
			m_AhphaChildList.remove( iter );
			break;
		}
	}
}

void DDObject::DeleteAlignedClass( DDObject* object )
{
	if ( object )
	{
		object->~DDObject();
		_aligned_free( object );
		object = nullptr;
	}
}
