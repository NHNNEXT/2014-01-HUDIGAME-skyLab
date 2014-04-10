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
	D3DXMatrixIdentity( &m_Matrix );
	D3DXMatrixIdentity( &m_MatrixTransform );
	D3DXMatrixIdentity( &m_MatrixRotation );
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

// �ۼ��� : �輺ȯ
// �ۼ��� : 14.04.06
// ���� : object�� affine��ȯ �� �ڽ� ��� render
void DDObject::Render()
{
	if ( m_Visible == false ) return;
		
	AffineTransfrom();
	RenderItSelf();
	RenderChildNodes();
}

void DDObject::Update( float dTime )
{
	if ( m_Visible == false ) return;
	
	UpdateItSelf( dTime );
	UpdateChildNodes( dTime );
}

void DDObject::AffineTransfrom()
{
	D3DXQUATERNION	qRotation;
	DDRenderer* renderer = DDRenderer::GetInstance();

	/*
	D3DXMatrixIdentity( &m_Matrix );
	// ���� ȸ�� �� ��ķ� �����
	D3DXMATRIXA16	currentRotation;
	D3DXQuaternionRotationYawPitchRoll( &qRotation, m_Rotation.y, m_Rotation.x, m_Rotation.z );
	D3DXMatrixTransformation( &currentRotation, NULL, NULL, NULL, NULL, &qRotation, NULL );

	// ����� �����ʹ� �ʱ�ȭ
	m_Rotation = DDVECTOR3( .0f, .0f, .0f );
	
	// ���� ȸ�� ��ȯ�� ��ġ��
	D3DXMatrixMultiply( &m_MatrixRotation, &m_MatrixRotation, &currentRotation );

	// �̵��� �������� �������
	D3DXMatrixTransformation( &m_MatrixTransform, NULL, NULL, &m_Scale, NULL, NULL, &m_Position );
	D3DXMatrixMultiply( &m_Matrix, &m_MatrixRotation, &m_MatrixTransform );

	// �θ��� ��ǥ�迡�� �� ��ȯ�� ��ǥ�踦 ���� ��Ų��!
	// �θ��� ������ ��ȯ�� ����
	if ( nullptr != m_pParent )
	{
		D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &m_pParent->GetMatrix() );
	}

	// �ڽ�+�θ��� ������ ��ȯ�� ������ǥ�迡 ����
	if ( FAILED( renderer->GetDevice()->SetTransform( D3DTS_WORLD, &m_Matrix ) ) )
	{
		// error 
		return;
	}

	// �θ� ��ǥ�踦 �޾ƿ���
	// �޾ƿ� ��ǥ�踦 ������� ���� �����ӿ��� ����� ȸ�� ��ȯ�� ������ ��ȯ�� ����
	// �̷��� ���� ��ǥ�� �ȿ��� ���� �����ؾ� �ϴ� ȸ�� ��ȯ ���� - ȸ�� ���� �����ؼ� ���� ������ �� ( �ٷ� �� ���ο��� Ȱ���� )
	// 
	*/


	D3DXMatrixIdentity( &m_Matrix );

	// rotation���� ���ʹϾ� ����, yaw ptich roll �� y, x, z ������
	D3DXQuaternionRotationYawPitchRoll( &qRotation, D3DXToRadian( m_Rotation.y ), D3DXToRadian( m_Rotation.x ), D3DXToRadian( m_Rotation.z) );

	// matrix�� affine��ȯ�� ����� ���·� ��ȯ	
	D3DXMatrixTransformation( &m_Matrix, NULL, NULL, &m_Scale, NULL, &qRotation, &m_Position );

	// �θ��� ��ǥ�迡�� �� ��ȯ�� ��ǥ�踦 ���� ��Ų��!
	// �θ��� ������ ��ȯ�� ����
	if ( nullptr != m_pParent )
	{
		D3DXMatrixMultiply( &m_Matrix, &m_pParent->GetMatrix(), &m_Matrix);
	}

	// �ڽ�+�θ��� ������ ��ȯ�� ������ǥ�迡 ����
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
