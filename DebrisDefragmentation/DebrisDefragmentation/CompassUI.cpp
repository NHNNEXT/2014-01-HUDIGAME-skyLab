#include "CompassUI.h"
#include "ObjectManager.h"


#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

struct CUSTOMVERTEX
{
	D3DXVECTOR3 position; // The position
	D3DCOLOR color;    // The color
	FLOAT tu, tv;   // The texture coordinates
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
	// if ( FAILED( D3DXCreateTextureFromFile( pD3DDevice, L".\\Resources\\3DModel\\banana.bmp", &m_pTexture ) ) )
	if ( FAILED( D3DXCreateTextureFromFile( pD3DDevice, L".\\Resources\\Image\\compass.png", &m_pTexture ) ) )
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
	{
		FLOAT theta = ( 2 * D3DX_PI * i ) / ( 50 - 1 );

		pVertices[2 * i + 0].position = D3DXVECTOR3( sinf( theta ) * 1.1f, -0.04f, cosf( theta ) * 1.1f );
		pVertices[2 * i + 0].color = 0x88ffffff;
		pVertices[2 * i + 0].tu = ( (FLOAT)i ) / ( 50 - 1 );
		pVertices[2 * i + 0].tv = 1.0f;

		pVertices[2 * i + 1].position = D3DXVECTOR3( sinf( theta ) * 1.1f, 0.04f, cosf( theta ) * 1.1f );
		pVertices[2 * i + 1].color = 0x88ffffff;
		pVertices[2 * i + 1].tu = ( (FLOAT)i ) / ( 50 - 1 );
		pVertices[2 * i + 1].tv = 0.0f;
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

	// rotation에서 쿼터니언 생성, yaw ptich roll 은 y, x, z 순서임
	D3DXQuaternionRotationYawPitchRoll( &qRotation, D3DXToRadian( m_Rotation.y ), D3DXToRadian( m_Rotation.x ), D3DXToRadian( m_Rotation.z ) );

	// matrix를 affine변환이 적용된 형태로 변환	
	D3DXMatrixTransformation( &m_Matrix, NULL, NULL, &m_Scale, NULL, &qRotation, &m_Position );
	
	
	/**** tilt transform ****/

	/* 각도를 구하는 과정 */
	// 내 위치는 m_Position에 m_Matrix를 곱한 결과 (월드 좌표계)
	D3DXMATRIXA16 parentTransform = m_pParent->GetMatrix();
	D3DXMatrixMultiply( &parentTransform, &m_Matrix, &parentTransform );

	D3DXVECTOR4 tempPos;
	D3DXVec3Transform( &tempPos, &m_Position, &parentTransform );
	DDVECTOR3 currentPos( tempPos.x, tempPos.y, tempPos.z );

	// ISS의 위치는 ISS의 위치 그대로 사용 - 이미 월드 좌표계
	DDVECTOR3 IssDirection = GObjectManager->GetIssPosition() - currentPos;

	// 위에서 구한 상대 좌표에 의한 벡터를 다시 현재 계산이 진행되는 로컬 좌표계 기준으로 변환 - 로컬 좌표계의 z벡터와 계산이 필요하므로 회전이 적용되어야 한다
	D3DXVECTOR4 tempDirection;
	D3DXVec3Transform( &tempDirection, &IssDirection, &parentTransform );
	IssDirection = DDVECTOR3( tempDirection.x, tempDirection.y, tempDirection.z );


	// 이렇게 구한 벡터를 xy평면에 투영하고, 단위 벡터로 만들자
	float directionYLength = D3DXVec3Dot( &DDVECTOR3( 0.0f, 1.0f, 0.0f ), &IssDirection );
	float directionXLength = D3DXVec3Dot( &DDVECTOR3( 1.0f, 0.0f, 0.0f ), &IssDirection );

	DDVECTOR3 projectedVector = ( directionYLength * DDVECTOR3( 0.0f, 1.0f, 0.0f ) ) + ( directionXLength * DDVECTOR3( 1.0f, 0.0f, 0.0f ) );
	D3DXVec3Normalize( &projectedVector, &projectedVector );

	// x축과 투영된 벡터의 사이 각도를 구하자 - 회전할 각도
	float angle = acos( (float)D3DXVec3Dot( &projectedVector, &DDVECTOR3( 1.0f, 0.0f, 0.0f ) ) );

	/* 회전 축을 구하는 과정 */
	// 이건 z축이다.
	
	float tempSign = -directionYLength / abs( directionYLength );

	/* 실제로 회전을 적용하는 과정 */
	D3DXMATRIXA16 tiltTransform;
	D3DXMatrixRotationAxis( &tiltTransform, &DDVECTOR3( 0.0f, 0.0f, 1.0f ), tempSign * angle );
	
	
	/**** look-at transform ****/
	
	/* 각도를 구하는 과정 */
	// 회전할 각도는 z축과 ISS로 향하는 사이 각도를 구하면 된다.
	DDVECTOR3 IssDirectionUnit;
	D3DXVec3Normalize( &IssDirectionUnit, &IssDirection );
	angle = acos( (float)D3DXVec3Dot( &IssDirectionUnit, &DDVECTOR3( 0.0f, 0.0f, 1.0f ) ) );

	/* 회전 축을 구하는 과정 */
	// 회전축은 로컬 좌표계의 y축을 tilt transform한 결과
	D3DXVECTOR4 tempAxis;
	D3DXVec3Transform( &tempAxis, &DDVECTOR3( 0.0f, 1.0f, 0.0f ), &tiltTransform );
	DDVECTOR3 rotationAxis( tempAxis.x, tempAxis.y, tempAxis.z );

	/* 회전을 적용하는 과정 */
	D3DXMATRIXA16 lookatTransform;
	D3DXMatrixRotationAxis( &lookatTransform, &rotationAxis, - angle * 2 );

	D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &tiltTransform );
	D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &lookatTransform );
	

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

	LPDIRECT3DDEVICE9 pD3DDevice = DDRenderer::GetInstance()->GetDevice();
	
	/*
	모델 그리기는 일시적으로 주석처리
	지금은 직접 버텍스 버퍼에 점 찍어 놓고 그걸로 그림 - 아래 참조
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


	// 조심해!!
	// alpha blending.. 안먹음
	pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	// alpha testing.. 문제는 콤파스의 알파를 날려버린다는거.. 안보임 ㄷㄷ
	pD3DDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
	pD3DDevice->SetRenderState( D3DRS_ALPHAREF, 0x00000088 );
	pD3DDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );


	// Render the vertex buffer contents
	pD3DDevice->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX ) );
	pD3DDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
	pD3DDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 * 50 - 2 );
}
