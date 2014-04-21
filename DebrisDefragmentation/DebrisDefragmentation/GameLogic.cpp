﻿#include "stdafx.h"
#include "GameLogic.h"
#include "PlayScene.h"
#include "NetworkManager.h"

GameLogic* GGameLogic = nullptr;

GameLogic::GameLogic()
{
	for ( unsigned int playerId = 0; playerId < MAX_PLAYER_NUM; ++playerId )
	{
		m_PlayerList[playerId] = nullptr;
	}
}


GameLogic::~GameLogic()
{
}

void GameLogic::Init()
{
	m_PrevTime = timeGetTime();
	// InitializeSRWLock( &m_SRWLock );
}

bool GameLogic::AddPlayer(int playerId)
{	
	if ( playerId < 0 || playerId >= MAX_PLAYER_NUM )
		return false;

	// 캐릭터 없으면 리턴
	if ( m_PlayerList[playerId] != nullptr )
		return false;

	// 새 캐릭터 만듦
	m_PlayerList[playerId] = Player::Create(playerId);
	m_PlayerList[playerId]->Init();

	m_Scene->AddChild( m_PlayerList[playerId] );
	++m_CurrentPlayers;

	// 처음 연결일 때, 현재 사용자의 플레이어일 것이므로 player ID set
	if ( GNetworkManager->GetMyPlayerId() == -1 )
	{
		GNetworkManager->SetMyPlayerId( playerId );
	}
	

	return true;
}

void GameLogic::DeletePlayer( int playerId )
{
	if ( m_PlayerList[playerId] != nullptr )
	{
		delete m_PlayerList[playerId];
		m_PlayerList[playerId] = nullptr;

		--m_CurrentPlayers;
	}
}

DDScene* GameLogic::CreateScene( std::wstring sceneName )
{
	m_Scene = PlayScene::Create( sceneName );
	m_Scene->Init();
	return m_Scene;
}


// 모든 캐릭터의 위치정보를 업데이트 한다. 게임 시작(누군가 새로 들어왓을 때 해야할 부분)
void GameLogic::Update()
{
// 	DWORD currentTime = timeGetTime();
// 	float dt = ( static_cast<float>( currentTime - m_PrevTime ) ) / 1000.f;
// 	m_PrevTime = currentTime;
// 
// 	for ( unsigned int playerId = 0; playerId < MAX_PLAYER_NUM; ++playerId )
// 	{
// 		if ( m_PlayerList[playerId] != nullptr )
// 		{
// 			//m_PlayerList[playerId]->update( dt );
// 		}
// 	}
}

// 특정 플레이어의 상태정보를 업데이트한다.
void GameLogic::UpdatePlayerMove( int playerId, DDVECTOR3 pos, DDVECTOR3 vel, DDVECTOR3 rot )
{
	m_PlayerList[playerId]->SetPosition( pos );
	m_PlayerList[playerId]->SetVelocity( vel );
	m_PlayerList[playerId]->SetRotation( rot );	
	m_PlayerList[playerId]->GoForward();
}

void GameLogic::UpdatePlayerStop( int playerId, DDVECTOR3 pos )
{
	m_PlayerList[playerId]->SetPosition( pos );
	m_PlayerList[playerId]->Stop();
}

void GameLogic::UpdatePlayerRotation( int playerId, DDVECTOR3 rot )
{
	m_PlayerList[playerId]->SetRotation( rot );
}

void GameLogic::UpdatePlayerSync( int playerId, DDVECTOR3 pos, DDVECTOR3 vel, DDVECTOR3 rot )
{
	m_PlayerList[playerId]->SetPosition( pos );
	m_PlayerList[playerId]->SetVelocity( vel );
	m_PlayerList[playerId]->SetRotation( rot );
}

void GameLogic::UpdatePlayerNew( int playerId, DDVECTOR3 pos, DDVECTOR3 vel, DDVECTOR3 acc, DDVECTOR3 rot )
{
	m_PlayerList[playerId]->SetPosition( pos );
	m_PlayerList[playerId]->SetVelocity( vel );
	m_PlayerList[playerId]->SetRotation( rot );
	m_PlayerList[playerId]->SetAcceleration( acc );
}


bool GameLogic::SetPosition( unsigned int playerId, float x, float y, float z )
{ 
	m_PlayerList[playerId]->SetPosition( x, y, z ); 

	return true;
}

bool GameLogic::SetScale( unsigned int playerId, float scaleX, float scaleY, float scaleZ )
{ 
	m_PlayerList[playerId]->SetScale( scaleX, scaleY, scaleZ );

	return true;
}

bool GameLogic::SetRotation( unsigned int playerId, float rotationX, float rotationY, float rotationZ )
{ 
	m_PlayerList[playerId]->SetRotation( rotationX, rotationY, rotationZ );

	return true;
}

bool GameLogic::SetAcceleration( unsigned int playerId )
{ 
	m_PlayerList[playerId]->GoForward( );

	return true;
}

bool GameLogic::Stop( unsigned int playerId )
{ 
	m_PlayerList[playerId]->Stop( );

	return true;
}

bool GameLogic::RotateDicrection( unsigned int playerId, float x, float y )
{
	m_PlayerList[playerId]->RotateDicrection( x, y );

	return true;
}

DDVECTOR3 GameLogic::GetPosition( unsigned int playerId )
{ 
	return m_PlayerList[playerId]->GetPosition(); 
}

DDVECTOR3 GameLogic::GetScale( unsigned int playerId )
{ 
	return m_PlayerList[playerId]->GetScale(); 
}

DDVECTOR3 GameLogic::GetRotation( unsigned int playerId )
{ 
	return m_PlayerList[playerId]->GetRotation(); 
}

DDVECTOR3 GameLogic::GetVelocity( unsigned int playerId )
{
	return m_PlayerList[playerId]->GetVelocity();
}

