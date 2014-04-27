#include "CompassUI.h"
#include "ObjectManager.h"

CompassUI::CompassUI()
{
	SetPosition( 0.0f, 0.0f, 0.0f );
}

CompassUI::CompassUI( std::wstring modelPath ) : DDModel( modelPath )
{
}

CompassUI::~CompassUI()
{
}

void CompassUI::RenderItSelf()
{
	// 부모의 행렬 변환을 가져와서 월드 좌표계 기반으로 내 위치를 계산
	m_Matrix = m_pParent->GetMatrix();

	D3DXVECTOR4 tempPos;
	D3DXVec3Transform( &tempPos, &m_Position, &m_Matrix );
	DDVECTOR3 currentPos( tempPos.x, tempPos.y, tempPos.z );

	// 현재 카메라의 위치에서 ISS의 위치로 향하는 벡터를 구한다.
	DDVECTOR3 IssDirection = GObjectManager->GetIssPosition() - currentPos;

	// 카메라의 z축과 x축을 노멀라이즈해서 가지고 있자
	DDVECTOR3 cameraAxisZ = m_pParent->GetViewDirection();
	D3DXVec3Normalize( &cameraAxisZ, &IssDirection );

	DDVECTOR3 cameraAxisX = m_pParent->GetAxisX();
	D3DXVec3Normalize( &cameraAxisX, &cameraAxisX );

	// 먼저 카메라의 z축을 축으로 compass ring을 회전시킨다
	// 회전시키는 각도는 ISS를 카메라의 z축에 투영한 점과 ISS의 위치를 잇는 벡터
	// ISS의 위치를 카메라의 xz 평면에 투영한 점과 앞에서 z축에 투영시킨 ISS의 위치를 잇는 벡터

	// ISS의 위치를 카메라의 z축에 투영시킨 지점은 카메라의 위치와 ISS의 위치를 잇는 벡터를 
	// z축에 내적해서 얻은 값에 z축 방향 벡터를 곱한 값을 다시 카메라의 위치에 더해서 얻는다
	float projectedLength = D3DXVec3Dot( &cameraAxisZ, &IssDirection );
	DDVECTOR3 prjectedPoint( currentPos + cameraAxisZ * projectedLength );
	
	// 이렇게 얻은 지점과 ISS를 잇는 벡터는 카메라의 xy평면에 평행하다
	DDVECTOR3 prjectedVector( GObjectManager->GetIssPosition() - prjectedPoint );
	D3DXVec3Normalize( &prjectedVector, &prjectedVector );

	// 앞에서 구한 벡터와 카메라의 x축이 이루는 각도를 구한다.
	float angle = acos( (float)D3DXVec3Dot( &cameraAxisX, &prjectedVector ) );

	// compass ring을 앞에서 구한 각도만큼 z축을 기준으로 회전시킨다.
	D3DXMATRIX tiltTransform;
	D3DXMatrixRotationAxis( &tiltTransform, &cameraAxisZ, angle );

	// 부모로부터 얻은 변환 행렬에 지금 구한 회전 변환을 추가한다.
	D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &tiltTransform );

	// 위의 회전을 완료하면 compass ring의 중심은 현재 화면의 중심을 지나고, compass ring은 기울어진 상태
	// 다시 말해 화면을 compass ring이 사선으로 가로지르고 있는 상태가 되어야 하는데....







	// 이번에는 compass ring을 두 벡터의 사이 각도만큼 회전시킨다
	// 두 벡터는 다음과 같다
	// 카메라의 위치와 compass ring의 원점을 잇는 벡터 (카메라의 z축)
	// 카메라의 위치와 ISS의 위치를 잇는 벡터
	// 회전 축 : 두 벡터를 외적한 벡터

	

	

	// 정면을 바라보는 벡터와 ISS로 향하는 벡터의 사이각을 구한다.
	// 노멀라이즈 할 것
	DDVECTOR3 normalIssDirection;

	D3DXVec3Normalize( &cameraAxisZ, &cameraAxisZ );
	angle = acos( (float)D3DXVec3Dot( &cameraAxisZ, &normalIssDirection ) );

	// 카메라의 z축과 카메라의 위치와 ISS의 위치를 잇는 벡터를 외적해서 수직인 벡터를 찾는다.
	DDVECTOR3 rotationAxis;
	D3DXVec3Cross( &rotationAxis, &cameraAxisZ, &IssDirection );

	// 회전변환 행렬 생성
	D3DXMATRIX lookAtIssTransform;
	D3DXMatrixRotationAxis( &lookAtIssTransform, &rotationAxis, angle );

	// 부모인 카메라의 변환 행렬에 ISS로 향하게 하는 변환 행렬을 곱한다.
	D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &lookAtIssTransform );

	// 자신+부모의 어파인 변환을 월드좌표계에 적용
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
