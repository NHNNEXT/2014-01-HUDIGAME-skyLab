#include "stdafx.h"
#include "Player.h"
#include "CharacterModel.h"
#include "NetworkManager.h"
#include "PlayerManager.h"

#include "Physics.h"

Player::Player()
{
}

Player::Player( int playerId )
{
	// 조심해!!
	// 나중에 인자 입력받아서 클래스 종류별로 m_avatar에 지정해줄 것
	m_ClassComponent = ClassComponent::Create();
	m_PlayerId = playerId;
}


Player::~Player()
{
}

void Player::Init()
{	
	InitCollisionBox();

	// dummy player 일 경우 character model을 추가하지 않는다.
	if ( m_PlayerId > REAL_PLAYER_NUM - 1 )
	{		
		return;
	}

	m_CharacterModel = CharacterModel::Create( L"spaceMan.x" );	
	AddChild( m_CharacterModel );
	
	// 내 캐릭터의 visible 끔.	
	if ( GNetworkManager->GetMyPlayerId() == m_PlayerId )
	{
		m_CharacterModel->SetVisible( false );
	}

}



void Player::RenderItSelf()
{
	// 자전 변환을 m_Matrix에 추가해서 자식 객체들 - 카메라, 캐릭터 등이 
	// 자전 변환이 적용된 상태로 계산되게 한다

	if ( m_ClassComponent->IsSpinning( ) )
	{
		// 조심해!!
		// affine transform에 적용해서 한 번에 처리하는 게 좋을 듯
		m_ClassComponent->AddSpinTime( 0.02 );

		// 회전축을 기준으로 물체를 회전시킵니다.
		D3DXMATRIXA16 spinTransform;
		D3DXMatrixRotationAxis( &spinTransform, &m_RigidBody.m_SpinAxis, m_RigidBody.m_SpinAngle * m_ClassComponent->GetSpinTime( ) );
		D3DXMatrixMultiply( &m_Matrix, &spinTransform, &m_Matrix );
	}

	DrawCollisionBox();
}


void Player::UpdateItSelf( float dTime )
{
	
	//printf_s( "OXYGEN REMAIN : %d\n", m_Avatar->GetOxygen() );
	if ( !m_ClassComponent->CheckRemainOxygen() && !m_ClassComponent->IsAlive() )
	{
		printf( "player is dead\n" );
		GNetworkManager->SendDeadRequest();
		// return;
	}

	if ( m_ClassComponent->IsAccelerating() )
	{
		/// config.h
		if ( timeGetTime() - m_ClassComponent->GetAccelerationStartTime() > ACCELERATION_TIME )
		{
			// 가속 끝났다
			m_ClassComponent->SetIsAccelerating( false );
			m_RigidBody.m_Acceleration = DDVECTOR3( 0, 0, 0 );
		}
	}

	Physics::CalcCurrentPosition( &m_Position, &m_RigidBody.m_Velocity, m_RigidBody.m_Acceleration, dTime );
}

void Player::LookAt( float x, float y, float z )
{
	g_PlayerManager->GetCamera()->IncreaseRotation( D3DXVECTOR3( x, y, z ) * MOUSE_ROTATION_SENSITIVITY );
}

void Player::TurnBody( float x, float y, float z )
{
	m_ClassComponent->TurnBody( m_Rotation, x, y, z );		
}

void Player::SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity )
{
	m_ClassComponent->SetSpin( rotationAxis, angularVelocity, m_RigidBody );
	m_ClassComponent->SetSpinTime( 0.0f );
	m_ClassComponent->SetSpinnigFlag( true );
}

void Player::AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity )
{
	m_ClassComponent->AddSpin( rotationAxis, angularVelocity, m_RigidBody );
	// m_SpinTime = 0.0f;
	m_ClassComponent->SetSpinnigFlag( true );
}

void Player::StopSpin( )
{
	m_ClassComponent->SetSpinnigFlag( false );
	m_ClassComponent->SetSpinTime( 0.0f );
	m_ClassComponent->StopSpin( m_RigidBody );
}

void Player::InitCollisionBox()
{
	// collision box는 어떤 객체이냐에 따라서 다르게 구현된다.
	m_CollisionBox.SetCenterPosition( D3DXVECTOR3( CHARACTER_CB_CENTER_POS_X, CHARACTER_CB_CENTER_POS_Y, CHARACTER_CB_CENTER_POS_Z ) );
	m_CollisionBox.SetLength( D3DXVECTOR3(CHARACTER_CB_LENGTH_X, CHARACTER_CB_LENGTH_Y, CHARACTER_CB_LENGTH_Z) );

	m_CollisionBox.InitAxisDir();
	m_CollisionBox.InitPointList();
	m_CollisionBox.InitRadius();
}

void Player::DrawCollisionBox()
{
	LPDIRECT3DDEVICE9 pD3DDevice = DDRenderer::GetInstance()->GetDevice();

	D3DXVECTOR4 tempMat;
	D3DXVECTOR3 currentPos;
	D3DXVECTOR3 currentPoint[8];
	D3DXVECTOR3 currentAxis[3];

	// 각 점 좌표
	D3DXVec3Transform( &tempMat, &m_CollisionBox.m_PointList[0], &m_Matrix );
	currentPoint[0] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

	D3DXVec3Transform( &tempMat, &m_CollisionBox.m_PointList[1], &m_Matrix );
	currentPoint[1] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

	D3DXVec3Transform( &tempMat, &m_CollisionBox.m_PointList[2], &m_Matrix );
	currentPoint[2] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

	D3DXVec3Transform( &tempMat, &m_CollisionBox.m_PointList[3], &m_Matrix );
	currentPoint[3] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

	D3DXVec3Transform( &tempMat, &m_CollisionBox.m_PointList[4], &m_Matrix );
	currentPoint[4] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

	D3DXVec3Transform( &tempMat, &m_CollisionBox.m_PointList[5], &m_Matrix );
	currentPoint[5] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

	D3DXVec3Transform( &tempMat, &m_CollisionBox.m_PointList[6], &m_Matrix );
	currentPoint[6] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

	D3DXVec3Transform( &tempMat, &m_CollisionBox.m_PointList[7], &m_Matrix );
	currentPoint[7] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

	// 그리기
	D3DXMATRIX projMat, viewMat;
	pD3DDevice->GetTransform( D3DTS_PROJECTION, &projMat );
	pD3DDevice->GetTransform( D3DTS_VIEW, &viewMat );
	viewMat *= projMat;

	ID3DXLine *Line;

	if ( D3DXCreateLine( pD3DDevice, &Line ) != D3D_OK )
		return;
	Line->SetWidth( 0.5 );
	Line->SetAntialias( true );

	D3DXVECTOR3 point[11];
	point[0] = currentPoint[0];
	point[1] = currentPoint[1];
	point[2] = currentPoint[2];
	point[3] = currentPoint[3];
	point[4] = currentPoint[0];
	point[5] = currentPoint[4];
	point[6] = currentPoint[5];
	point[7] = currentPoint[6];
	point[8] = currentPoint[7];
	point[9] = currentPoint[4];
	Line->Begin();

	// 조심해!!!
	// dummy 용 임시, 더미 플레이어 제거시 제거할 것.
	if ( m_PlayerId > REAL_PLAYER_NUM - 1 )
	{
		Line->DrawTransform( point, 10, &viewMat, D3DXCOLOR( .0f, 1.0f, .0f, 1.0f ) );

		// 비어 있는 선 그리기
		D3DXVECTOR3 pointT[2];
		pointT[0] = currentPoint[7];
		pointT[1] = currentPoint[3];
		Line->DrawTransform( pointT, 2, &viewMat, D3DXCOLOR( .0f, 1.0f, .0f, 1.0f ) );

		pointT[0] = currentPoint[6];
		pointT[1] = currentPoint[2];
		Line->DrawTransform( pointT, 2, &viewMat, D3DXCOLOR( .0f, 1.0f, .0f, 1.0f ) );

		pointT[0] = currentPoint[5];
		pointT[1] = currentPoint[1];
		Line->DrawTransform( pointT, 2, &viewMat, D3DXCOLOR( .0f, 1.0f, .0f, 1.0f ) );

		Line->End();
		Line->Release();
		return;
	}


	Line->DrawTransform( point, 10, &viewMat, D3DXCOLOR( 1.0f, 0.0f, 1.0f, 1.0f ) );

	// 비어 있는 선 그리기
	D3DXVECTOR3 pointT[2];
	pointT[0] = currentPoint[7];
	pointT[1] = currentPoint[3];
	Line->DrawTransform( pointT, 2, &viewMat, D3DXCOLOR( 1.0f, 0.0f, 1.0f, 1.0f ) );

	pointT[0] = currentPoint[6];
	pointT[1] = currentPoint[2];
	Line->DrawTransform( pointT, 2, &viewMat, D3DXCOLOR( 1.0f, 0.0f, 1.0f, 1.0f ) );

	pointT[0] = currentPoint[5];
	pointT[1] = currentPoint[1];
	Line->DrawTransform( pointT, 2, &viewMat, D3DXCOLOR( 1.0f, 0.0f, 1.0f, 1.0f ) );

	Line->End();
	Line->Release();
}

// 캐릭터 클래스 변환시 실행, 내용은 server쪽과 동일하면 될 듯..
void Player::ChangeClass( CharacterClass characterClass )
{
	switch ( characterClass )
	{
		case CharacterClass::NO_CLASS:
			break;
		case CharacterClass::STRIKER:
			break;
		case CharacterClass::ENGINEER:
			break;
		case CharacterClass::PROTECTOR:
			break;
		default:
			break;
	}
}
