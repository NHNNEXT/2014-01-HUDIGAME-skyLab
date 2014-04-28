#include "CompassUI.h"
#include "ObjectManager.h"

CompassUI::CompassUI()
{
}

CompassUI::CompassUI( std::wstring modelPath ) : DDModel( modelPath )
{
}

CompassUI::~CompassUI()
{
}

void CompassUI::UpdateItSelf( float dTime )
{
	UNREFERENCED_PARAMETER( dTime );
}

void CompassUI::RenderItSelf()
{
	/*
	D3DXQUATERNION	qRotation;
	D3DXMatrixIdentity( &m_Matrix );
	// rotation���� ���ʹϾ� ����, yaw ptich roll �� y, x, z ������
	D3DXQuaternionRotationYawPitchRoll( &qRotation, D3DXToRadian( m_Rotation.y ), D3DXToRadian( m_Rotation.x ), D3DXToRadian( m_Rotation.z ) );

	// matrix�� affine��ȯ�� ����� ���·� ��ȯ	
	D3DXMatrixTransformation( &m_Matrix, NULL, NULL, &m_Scale, NULL, &qRotation, &DDVECTOR3( 0.0f, 0.0f, 3.0f ) );

	// �θ��� ��ǥ�迡�� �� ��ȯ�� ��ǥ�踦 ���� ��Ų��!
	// �θ��� ������ ��ȯ�� ����
	if ( nullptr != m_pParent )
	{
		// D3DXMatrixMultiply( &m_Matrix, &m_pParent->GetMatrix(), &m_Matrix);
		D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &m_pParent->GetParent()->GetMatrix() );
	}
	
	*/
	m_Matrix = m_pParent->GetMatrix();

	// �θ��� ��� ��ȯ�� �����ͼ� ���� ��ǥ�� ������� �� ��ġ�� ���
	//m_Matrix = m_pParent->GetParent()->GetMatrix();
	
	D3DXVECTOR4 tempPos;
	D3DXVec3Transform( &tempPos, &DDVECTOR3( 0.0f, 0.0f, 1.0f ), &m_Matrix );
	DDVECTOR3 currentPos( tempPos.x, tempPos.y, tempPos.z );

	// ���� ī�޶��� ��ġ���� ISS�� ��ġ�� ���ϴ� ���͸� ���Ѵ�.
	DDVECTOR3 IssDirection = GObjectManager->GetIssPosition() - currentPos;

	// ī�޶��� z��� x���� ��ֶ������ؼ� ������ ����
	D3DXVECTOR4 tempAxisZ;
	D3DXVec3Transform( &tempAxisZ, &DDVECTOR3( 0.0f, 0.0f, 1.0f ), &m_Matrix );
	DDVECTOR3 cameraAxisZ( tempAxisZ.x, tempAxisZ.y, tempAxisZ.z );
	// DDVECTOR3 cameraAxisZ = m_pParent->GetParent()->GetViewDirection();
	D3DXVec3Normalize( &cameraAxisZ, &IssDirection );

	D3DXVECTOR4 tempAxisX;
	D3DXVec3Transform( &tempAxisX, &DDVECTOR3( 1.0f, 0.0f, 0.0f ), &m_Matrix );
	DDVECTOR3 cameraAxisX( tempAxisX.x, tempAxisX.y, tempAxisX.z );
	D3DXVec3Normalize( &cameraAxisX, &cameraAxisX );

	// ���� ī�޶��� z���� ������ compass ring�� ȸ����Ų��
	// ȸ����Ű�� ������ ISS�� ī�޶��� z�࿡ ������ ���� ISS�� ��ġ�� �մ� ����
	// ISS�� ��ġ�� ī�޶��� xz ��鿡 ������ ���� �տ��� z�࿡ ������Ų ISS�� ��ġ�� �մ� ����

	// ISS�� ��ġ�� ī�޶��� z�࿡ ������Ų ������ ī�޶��� ��ġ�� ISS�� ��ġ�� �մ� ���͸� 
	// z�࿡ �����ؼ� ���� ���� z�� ���� ���͸� ���� ���� �ٽ� ī�޶��� ��ġ�� ���ؼ� ��´�
	float projectedLength = D3DXVec3Dot( &cameraAxisZ, &IssDirection );
	DDVECTOR3 prjectedPoint( currentPos + ( cameraAxisZ * projectedLength ) );
	
	// �̷��� ���� ������ ISS�� �մ� ���ʹ� ī�޶��� xy��鿡 �����ϴ�
	DDVECTOR3 prjectedVector( GObjectManager->GetIssPosition() - prjectedPoint );
	D3DXVec3Normalize( &prjectedVector, &prjectedVector );

	// �տ��� ���� ���Ϳ� ī�޶��� x���� �̷�� ������ ���Ѵ�.
	float angle = acos( (float)D3DXVec3Dot( &cameraAxisX, &prjectedVector ) );
	// compass ring�� �տ��� ���� ������ŭ z���� �������� ȸ����Ų��.
	D3DXMATRIXA16 tiltTransform;
	// D3DXMatrixRotationAxis( &tiltTransform, &cameraAxisZ, angle );
	D3DXMatrixRotationAxis( &tiltTransform, &cameraAxisZ, 0 );


	// ���� ȸ���� �Ϸ��ϸ� compass ring�� �߽��� ���� ȭ���� �߽��� ������, compass ring�� ������ ����
	// �ٽ� ���� ȭ���� compass ring�� �缱���� ���������� �ִ� ���°� �Ǿ�� �ϴµ�....
	/*






	// �̹����� compass ring�� �� ������ ���� ������ŭ ȸ����Ų��
	// �� ���ʹ� ������ ����
	// ī�޶��� ��ġ�� compass ring�� ������ �մ� ���� (ī�޶��� z��)
	// ī�޶��� ��ġ�� ISS�� ��ġ�� �մ� ����
	// ȸ�� �� : �� ���͸� ������ ����

	

	

	// ������ �ٶ󺸴� ���Ϳ� ISS�� ���ϴ� ������ ���̰��� ���Ѵ�.
	// ��ֶ����� �� ��
	DDVECTOR3 normalIssDirection;

	D3DXVec3Normalize( &cameraAxisZ, &cameraAxisZ );
	angle = acos( (float)D3DXVec3Dot( &cameraAxisZ, &normalIssDirection ) );

	// ī�޶��� z��� ī�޶��� ��ġ�� ISS�� ��ġ�� �մ� ���͸� �����ؼ� ������ ���͸� ã�´�.
	DDVECTOR3 rotationAxis;
	D3DXVec3Cross( &rotationAxis, &cameraAxisZ, &IssDirection );

	// ȸ����ȯ ��� ����
	D3DXMATRIX lookAtIssTransform;
	D3DXMatrixRotationAxis( &lookAtIssTransform, &rotationAxis, angle );

	// �θ�κ��� ���� ��ȯ ��Ŀ� ���� ���� ȸ�� ��ȯ�� �߰��Ѵ�.
	D3DXMatrixMultiply( &tiltTransform, &tiltTransform, &lookAtIssTransform );
	*/
	// �θ��� ī�޶��� ��ȯ ��Ŀ� ISS�� ���ϰ� �ϴ� ��ȯ ����� ���Ѵ�.
	D3DXMatrixMultiply( &m_Matrix, &tiltTransform, &m_Matrix );
	// D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &tiltTransform );


	// �ڽ�+�θ��� ������ ��ȯ�� ������ǥ�迡 ����
	if ( FAILED( DDRenderer::GetInstance()->GetDevice()->SetTransform( D3DTS_WORLD, &m_Matrix ) ) )
	{
		// error 
		return;
	}

	LPDIRECT3DDEVICE9 pD3DDevice = DDRenderer::GetInstance()->GetDevice();
	for ( DWORD i = 0; i < m_dwNumMaterials; ++i )
	{
		pD3DDevice->SetMaterial( &m_pMeshMaterials[i] );
		pD3DDevice->SetTexture( 0, m_pMeshTexture[i] );

		m_pMesh->DrawSubset( i );
	}
}
