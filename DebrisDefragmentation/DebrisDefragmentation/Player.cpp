#include "stdafx.h"
#include "Player.h"
#include "DDCamera.h"
#include "CharacterModel.h"
#include "NetworkManager.h"
#include "CompassUI.h"
#include "PlayerManager.h"

#include "Physics.h"

Player::Player()
{
}

Player::Player( int playerId )
{
	// 조심해!!
	// 나중에 인자 입력받아서 클래스 종류별로 m_avatar에 지정해줄 것
	m_CharacterClass = ClassComponent::Create();
	m_PlayerId = playerId;
}


Player::~Player()
{
}

void Player::Init()
{
	// 안되면 바꾸세요..ㅠㅠ 일단 이동, 충돌, 푸쉬풀은 확인 했음(단 iss에서 많이 벗어날 경우는...)
	//m_CharacterModel = CharacterModel::Create( L"debris.x" );
	m_CharacterModel = CharacterModel::Create( L"spaceMan.x" );
	//m_CharacterModel->SetScale( .5f, .5f, .5f );
	AddChild( m_CharacterModel );

	if ( GNetworkManager->GetMyPlayerId() == m_PlayerId )
	{
		// camera 설정
		m_Camera = DDCamera::Create();
		AddChild( m_Camera );
		g_PlayerManager->SetCamera( m_Camera );
		
		// 콤파스 설정
		CompassUI* compassUI = CompassUI::Create( L"tiger.x" );
		compassUI->Init();
		m_Camera->AddChild( compassUI );
		
		// 내 캐릭터의 visible 끔.
		m_CharacterModel->SetVisible( false );
	}
	/// config.h
	
}



void Player::RenderItSelf()
{
	// 자전 변환을 m_Matrix에 추가해서 자식 객체들 - 카메라, 캐릭터 등이 
	// 자전 변환이 적용된 상태로 계산되게 한다

	if ( m_CharacterClass->IsSpinning( ) )
	{
		// 조심해!!
		// affine transform에 적용해서 한 번에 처리하는 게 좋을 듯
		m_CharacterClass->AddSpinTime( 0.02 );

		// 회전축을 기준으로 물체를 회전시킵니다.
		D3DXMATRIXA16 spinTransform;
		D3DXMatrixRotationAxis( &spinTransform, &m_RigidBody.m_SpinAxis, m_RigidBody.m_SpinAngle * m_CharacterClass->GetSpinTime( ) );
		D3DXMatrixMultiply( &m_Matrix, &spinTransform, &m_Matrix );
	}
}


void Player::UpdateItSelf( float dTime )
{
	//printf_s( "OXYGEN REMAIN : %d\n", m_Avatar->GetOxygen() );
	if ( !m_CharacterClass->CheckRemainOxygen() )
	{
		// printf( "player is dead" );
		// return;
	}

	if ( m_CharacterClass->IsAccelerating() )
	{
		/// config.h
		if ( timeGetTime() - m_CharacterClass->GetAccelerationStartTime() > 500 )
		{
			// 가속 끝났다
			m_CharacterClass->SetIsAccelerating( false );
			m_RigidBody.m_Acceleration = DDVECTOR3( 0, 0, 0 );
		}
	}

	Physics::CalcCurrentPosition( &m_Position, &m_RigidBody.m_Velocity, m_RigidBody.m_Acceleration, dTime );
}

void Player::LookAt( float x, float y, float z )
{
	g_PlayerManager->GetCamera()->IncreaseRotation( D3DXVECTOR3( x, y, z ) * MOUSE_ROTATION_WEIGHT );
}

void Player::TurnBody( float x, float y, float z )
{
	m_CharacterClass->TurnBody( m_Rotation, x, y, z ); 
	g_PlayerManager->GetCamera()->SetRotation( ZERO_VECTOR3 );
}

void Player::SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity )
{
	m_CharacterClass->SetSpin( rotationAxis, angularVelocity, m_RigidBody );
	m_CharacterClass->SetSpinTime( 0.0f );
	m_CharacterClass->SetSpinnigFlag( true );
}

void Player::AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity )
{
	m_CharacterClass->AddSpin( rotationAxis, angularVelocity, m_RigidBody );
	// m_SpinTime = 0.0f;
	m_CharacterClass->SetSpinnigFlag( true );
}

void Player::StopSpin( )
{
	m_CharacterClass->SetSpinnigFlag( false );
	m_CharacterClass->SetSpinTime( 0.0f );
	m_CharacterClass->StopSpin( m_RigidBody );
}