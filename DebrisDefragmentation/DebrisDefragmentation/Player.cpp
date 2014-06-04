#include "stdafx.h"
#include "Player.h"
#include "CharacterModel.h"
#include "NetworkManager.h"
#include "PlayerManager.h"
#include "Striker.h"
#include "Engineer.h"
#include "Protector.h"

#include "Physics.h"
#include "MatrixTransform.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include "DDCamera.h"
#include "Environment.h"

Player::Player()
{
}

Player::Player( int playerId, CharacterClass characterClass )
{
	m_PlayerId = playerId;
	m_ClassComponent = ClassComponent::Create( characterClass );
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

	//m_CharacterModel = CharacterModel::Create( L"spaceMan.x" );	
	m_CharacterModel = CharacterModel::Create();
	m_CharacterModel->SetModelMesh( GSceneManager->GetScene()->GetModelPool().GetModel(ModelType::PLAYER_MODEL) );

	// 조심해!!
	// 림라이트 관련 Shader 초기화 소스. 일단 주석
	//m_CharacterModel->InitFX( L"Rimlight.fx" );
	//m_CharacterModel->InitFX( L"red.fx" );
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

	if ( IsSpinning( ) )
	{
		// 조심해!!
		// affine transform에 적용해서 한 번에 처리하는 게 좋을 듯
		AddSpinTime( 0.02f );

		// 회전축을 기준으로 물체를 회전시킵니다.
		D3DXMATRIXA16 spinTransform;
		D3DXVECTOR3 tmpSpinAxis = GetSpinAxis();
		float tmpSpinAngle = GetSpinAngularVelocity();
		D3DXMatrixRotationAxis( &spinTransform, &tmpSpinAxis, tmpSpinAngle * GetSpinTime( ) );
		D3DXMatrixMultiply( &m_Matrix, &spinTransform, &m_Matrix );

// 		D3DXQUATERNION qt;
// 		D3DXVECTOR3 scl, pos;
// 		D3DXMatrixDecompose( &scl, &qt, &pos, &spinTransform );
// 		auto ypr = GameMatrix::QuaternionToYawPitchRoll( qt );
// 		
// 		g_PlayerManager->GetCamera()->GetTransform().IncreaseRotation( D3DXVECTOR3( std::get<1>( ypr ), std::get<0>( ypr ), std::get<2>( ypr ) ) );
	}

	DrawCollisionBox();
}

void Player::UpdateItSelf( float dTime )
{
	if ( !m_ClassComponent->IsAlive() )
	{
		return;
		//printf( "player is dead\n" );
		//GNetworkManager->SendDeadRequest();
	}

	//printf_s( "OXYGEN REMAIN : %d\n", m_Avatar->GetOxygen() );
	m_ClassComponent->Update( dTime );

 	if (IsAccelerating() )
 	{
 		/// config.h
 		if ( timeGetTime() - GetAccelerationStartTime() > ACCELERATION_TIME )
 		{
 			// 가속 끝났다
 			SetIsAccelerating( false );
 			SetAcceleration(ZERO_VECTOR3);
 		}
 	}

	if ( IsSpinning() )
	{
		AddSpinTime( dTime );

		// 회전축을 기준으로 물체를 회전시킵니다.
		D3DXMATRIXA16 spinTransform;
		D3DXVECTOR3 tmpSpinAxis = GetSpinAxis();
		float tmpSpinAngle = GetSpinAngularVelocity();
		D3DXMatrixRotationAxis( &spinTransform, &tmpSpinAxis, tmpSpinAngle * GetSpinTime() );
		D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &spinTransform );
	}

	D3DXVECTOR3 tmpVec3 = GetTransform().GetPosition();
	D3DXVECTOR3 tmpVel = GetVelocity();
	D3DXVECTOR3 tmpAcc = GetAcceleration();
	// printf_s( "%d : %f / %f / %f\n", m_PlayerId, tmpVel.x, tmpVel.y, tmpVel.z );
	Physics::CalcCurrentPosition( &tmpVec3, &tmpVel, tmpAcc, dTime );
	GetTransform().SetPosition( tmpVec3 );
	SetVelocity( tmpVel );
}

void Player::Move( const D3DXVECTOR3& direction )
{
	// 가속 시작 시점 기록 - 타임 스탬프로 문제 해결
	// 나중에는 타이머 만들어서 써볼까?
	m_AccelerationStartTime = timeGetTime();
	SetIsAccelerating( true );

	D3DXVECTOR3 normalVec;
	D3DXVec3Normalize( &normalVec, &direction );

	m_Rigidbody.m_Acceleration += ( normalVec * ACCELERATION_WEIGHT );
}

void Player::Stop()
{
	// 장비를 정지합니다. 어 안되잖아? 어? 저, 정지가 안 돼, 정지시킬 수가 없어. 안-돼!
	m_Rigidbody.m_Acceleration = ZERO_VECTOR3;
	m_Rigidbody.m_Velocity = ZERO_VECTOR3;
}

void Player::LookAt( float x, float y, float z )
{
	GPlayerManager->GetCamera()->GetTransform().IncreaseRotation( D3DXVECTOR3( x, y, z ) * MOUSE_ROTATION_SENSITIVITY );
}

void Player::SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity )
{
	m_Rigidbody.m_SpinAngularVelocity = angularVelocity;
	m_Rigidbody.m_SpinAxis = rotationAxis;
	SetSpinTime( 0.0f );
	SetSpinnigFlag( true );
}

void Player::AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity )
{
	UNREFERENCED_PARAMETER( rotationAxis );
	UNREFERENCED_PARAMETER( angularVelocity );
	// 조심해!!
	// 구현 중
}

void Player::StopSpin( )
{
	SetSpinnigFlag( false );
	SetSpinTime( 0.0f );
	m_Rigidbody.m_SpinAngularVelocity = 0.0f;
	m_Rigidbody.m_SpinAxis = ZERO_VECTOR3;
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
	// 변신!
	m_ClassComponent = ClassComponent::Create( characterClass );
}
