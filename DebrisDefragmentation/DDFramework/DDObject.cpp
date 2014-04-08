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
	// Release();
}

void DDObject::Release( )
{
	for ( const auto& child : m_ChildList )
	{
		RemoveChild( child.get() );
	}
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

	// 일단 부모의 변환을 가져온다!

	// 내 중첩 변환을 적용 시킨다!
























	/*
	// 자신의 누적된 좌표계 변환에 다시 변화를 추가한다!
	// rotation에서 쿼터니언 생성, yaw ptich roll 은 y, x, z 순서임
	D3DXQuaternionRotationYawPitchRoll( &qRotation, m_Rotation.y, m_Rotation.x, m_Rotation.z );

	// matrix를 affine변환이 적용된 형태로 변환	
	D3DXMATRIXA16 currentTransform;
	D3DXMatrixTransformation( &currentTransform, NULL, NULL, &m_Scale, &m_Position, &qRotation, &m_Position );
	
	// 적용된 데이터는 초기화
	m_Scale = DDVECTOR3(1, 1, 1);
	m_Rotation = DDVECTOR3( 0, 0, 0 );
	m_Position = DDVECTOR3( 0, 0, 0 );
	
	D3DXMatrixMultiply( &m_MatrixTransform, &m_MatrixTransform, &currentTransform );
	*/

	// rotation에서 쿼터니언 생성, yaw ptich roll 은 y, x, z 순서임
	D3DXQuaternionRotationYawPitchRoll( &qRotation, m_Rotation.y, m_Rotation.x, m_Rotation.z );

	// matrix를 affine변환이 적용된 형태로 변환	
	D3DXMatrixTransformation( &m_Matrix, NULL, NULL, &m_Scale, NULL, &qRotation, &m_Position );

	// 부모의 좌표계에다 내 변환된 좌표계를 누적 시킨다!
	// 부모의 어파인 변환을 적용
	if ( nullptr != m_pParent )
	{
		D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &m_pParent->GetMatrix( ) );
	}

	// 자신+부모의 어파인 변환을 월드좌표계에 적용
	if ( FAILED( renderer->GetDevice()->SetTransform( D3DTS_WORLD, &m_Matrix ) ) )
	{
		// error 
		return;
	}	
}

DDVECTOR3 DDObject::GetViewDirection( )
{
	return D3DXVECTOR3( m_Matrix._31, m_Matrix._32, m_Matrix._33 );
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
	std::shared_ptr<DDObject> object_ptr( object );
	object->SetParent( this );
	m_ChildList.push_back( object_ptr );
}

void DDObject::RemoveChild( DDObject* object )
{
	for ( auto& iter = m_ChildList.begin(); iter != m_ChildList.end(); iter++ )
	{
		if ( ( *iter ).get() == object )
		{
			//( *iter )->Release();
			//SafeDelete( *iter );
			m_ChildList.erase( iter );
			break;
		}
	}
}
