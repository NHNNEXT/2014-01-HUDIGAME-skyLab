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
	if ( GNetworkManager->GetMyPlayerId() == m_PlayerId )
	{
		m_Camera = DDCamera::Create();

		CompassUI* positionUI = CompassUI::Create( L"tiger.x" );
		m_Camera->AddChild(positionUI);
		
		AddChild( m_Camera );
		g_PlayerManager->SetCamera( m_Camera );
	}
	/// config.h
	m_CharacterModel = CharacterModel::Create( L"debris.x" );	
	m_CharacterModel->SetPosition( .0f, -1.0f, 2.0f );
	m_CharacterModel->SetScale( .5f, .5f, .5f );
	AddChild( m_CharacterModel );
}



void Player::RenderItSelf()
{

}


void Player::UpdateItSelf( float dTime )
{
	//printf_s( "OXYGEN REMAIN : %d\n", m_Avatar->GetOxygen() );
	if ( !m_CharacterClass->CheckRemainOxygen() )
	{
		printf( "player is dead" );
		return;
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