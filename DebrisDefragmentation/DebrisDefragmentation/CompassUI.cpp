#include "CompassUI.h"
#include "ObjectManager.h"


#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

struct CUSTOMVERTEX
{
	D3DXVECTOR3 position; // The position
	D3DCOLOR color;    // The color
};

CompassUI::CompassUI()
{
}

CompassUI::CompassUI( std::wstring modelPath ) : DDModel( modelPath )
{
	SetPosition( 0.0f, 0.0f, 0.0f );
}

CompassUI::~CompassUI()
{
}

void CompassUI::Init()
{
	LPDIRECT3DDEVICE9 pD3DDevice = DDRenderer::GetInstance()->GetDevice();

	// Use D3DX to create a texture from a file based image
	if ( FAILED( D3DXCreateTextureFromFile( pD3DDevice, L".\\Resources\\3DModel\\banana.bmp", &m_pTexture ) ) )
		return;

	// Create the vertex buffer.
	if ( FAILED( pD3DDevice->CreateVertexBuffer( 50 * 2 * sizeof( CUSTOMVERTEX ),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pVB, NULL ) ) )
	{
		return;
	}

	// Fill the vertex buffer. We are setting the tu and tv texture
	// coordinates, which range from 0.0 to 1.0
	CUSTOMVERTEX* pVertices;
	if ( FAILED( m_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
		return;

	for ( DWORD i = 0; i < 50; i++ )
	// for ( int i = 49; i >= 0; --i )
	{
		FLOAT theta = ( 2 * D3DX_PI * i ) / ( 50 - 1 );

		pVertices[2 * i + 0].position = D3DXVECTOR3( sinf( theta ) * 3.0f, -0.1f, cosf( theta ) * 3.0f );
		pVertices[2 * i + 0].color = 0xff880000;
		pVertices[2 * i + 1].position = D3DXVECTOR3( sinf( theta ) * 3.0f, 0.1f, cosf( theta ) * 3.0f );
		pVertices[2 * i + 1].color = 0xff880000;
	}
	m_pVB->Unlock();
}

void CompassUI::UpdateItSelf( float dTime )
{
	UNREFERENCED_PARAMETER( dTime );
}

void CompassUI::RenderItSelf()
{
	/**** affine transform ****/

	D3DXQUATERNION	qRotation;

	D3DXMatrixIdentity( &m_Matrix );

	// rotation���� ���ʹϾ� ����, yaw ptich roll �� y, x, z ������
	D3DXQuaternionRotationYawPitchRoll( &qRotation, D3DXToRadian( m_Rotation.y ), D3DXToRadian( m_Rotation.x ), D3DXToRadian( m_Rotation.z ) );

	// matrix�� affine��ȯ�� ����� ���·� ��ȯ	
	D3DXMatrixTransformation( &m_Matrix, NULL, NULL, &m_Scale, NULL, &qRotation, &m_Position );
	
	
	/**** tilt transform ****/

	/* ������ ���ϴ� ���� */
	// �� ��ġ�� m_Position�� m_Matrix�� ���� ��� (���� ��ǥ��)
	D3DXMATRIXA16 parentTransform = m_pParent->GetMatrix();
	D3DXMatrixMultiply( &parentTransform, &m_Matrix, &parentTransform );

	D3DXVECTOR4 tempPos;
	D3DXVec3Transform( &tempPos, &m_Position, &parentTransform );
	DDVECTOR3 currentPos( tempPos.x, tempPos.y, tempPos.z );

	// ISS�� ��ġ�� ISS�� ��ġ �״�� ��� - �̹� ���� ��ǥ��
	DDVECTOR3 IssDirection = GObjectManager->GetIssPosition() - currentPos;

	// ������ ���� ��� ��ǥ�� ���� ���͸� �ٽ� ���� ����� ����Ǵ� ���� ��ǥ�� �������� ��ȯ - ���� ��ǥ���� z���Ϳ� ����� �ʿ��ϹǷ� ȸ���� ����Ǿ�� �Ѵ�
	D3DXVECTOR4 tempDirection;
	D3DXVec3Transform( &tempDirection, &IssDirection, &parentTransform );
	IssDirection = DDVECTOR3( tempDirection.x, tempDirection.y, tempDirection.z );


	// �̷��� ���� ���͸� xy��鿡 �����ϰ�, ���� ���ͷ� ������
	float directionYLength = D3DXVec3Dot( &DDVECTOR3( 0.0f, 1.0f, 0.0f ), &IssDirection );
	float directionXLength = D3DXVec3Dot( &DDVECTOR3( 1.0f, 0.0f, 0.0f ), &IssDirection );

	DDVECTOR3 projectedVector = ( directionYLength * DDVECTOR3( 0.0f, 1.0f, 0.0f ) ) + ( directionXLength * DDVECTOR3( 1.0f, 0.0f, 0.0f ) );
	D3DXVec3Normalize( &projectedVector, &projectedVector );

	// x��� ������ ������ ���� ������ ������ - ȸ���� ����
	float angle = acos( (float)D3DXVec3Dot( &projectedVector, &DDVECTOR3( 1.0f, 0.0f, 0.0f ) ) );

	/* ȸ�� ���� ���ϴ� ���� */
	// �̰� z���̴�.
	
	float tempSign = -directionYLength / abs( directionYLength );

	/* ������ ȸ���� �����ϴ� ���� */
	D3DXMATRIXA16 tiltTransform;
	D3DXMatrixRotationAxis( &tiltTransform, &DDVECTOR3( 0.0f, 0.0f, 1.0f ), tempSign * angle );
	D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &tiltTransform );
	
	/**** look-at transform ****/
	
	/* ������ ���ϴ� ���� */
	// ȸ���� ������ z��� ISS�� ���ϴ� ���� ������ ���ϸ� �ȴ�.
	DDVECTOR3 IssDirectionUnit;
	D3DXVec3Normalize( &IssDirectionUnit, &IssDirection );
	angle = acos( (float)D3DXVec3Dot( &IssDirectionUnit, &DDVECTOR3( 0.0f, 0.0f, 1.0f ) ) );

	/* ȸ�� ���� ���ϴ� ���� */
	// ȸ������ ���� ��ǥ���� y���� tilt transform�� ���
	D3DXVECTOR4 tempAxis;
	D3DXVec3Transform( &tempAxis, &DDVECTOR3( 0.0f, 1.0f, 0.0f ), &tiltTransform );
	DDVECTOR3 rotationAxis( tempAxis.x, tempAxis.y, tempAxis.z );

	/* ȸ���� �����ϴ� ���� */
	D3DXMATRIXA16 lookatTransform;
	D3DXMatrixRotationAxis( &lookatTransform, &rotationAxis, -angle );
	D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &lookatTransform );
	

	// �θ��� ��ǥ�迡�� �� ��ȯ�� ��ǥ�踦 ���� ��Ų��!
	// �θ��� ������ ��ȯ�� ����
	if ( nullptr != m_pParent )
	{
		D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &m_pParent->GetMatrix() );
	}

	// �ڽ�+�θ��� ������ ��ȯ�� ������ǥ�迡 ����
	if ( FAILED( DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_WORLD, &m_Matrix ) ) )
	{
		// error 
		return;
	}

	LPDIRECT3DDEVICE9 pD3DDevice = DDRenderer::GetInstance()->GetDevice();
	
	/*
	�� �׸���� �Ͻ������� �ּ�ó��
	������ ���� ���ؽ� ���ۿ� �� ��� ���� �װɷ� �׸� - �Ʒ� ����
	for ( DWORD i = 0; i < m_dwNumMaterials; ++i )
	{
		pD3DDevice->SetMaterial( &m_pMeshMaterials[i] );
		pD3DDevice->SetTexture( 0, m_pMeshTexture[i] );

		m_pMesh->DrawSubset( i );
	}
	*/

	// set texture
	pD3DDevice->SetTexture( 0, m_pTexture );
	pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_DISABLE );

	// Render the vertex buffer contents
	pD3DDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX ) );
	pD3DDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
	pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 * 50 - 2 );
}
