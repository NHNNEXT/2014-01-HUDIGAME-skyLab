#include "stdafx.h"
#include "GameLogic.h"

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

int GameLogic::AddPlayer()
{
	for ( unsigned int playerId = 0; playerId < MAX_PLAYER_NUM; ++playerId )
	{
		if ( m_PlayerList[playerId] == nullptr )
		{
			m_PlayerList[playerId] = new PlayerCharacter( playerId );

			return playerId;
		}
	}

	return -1;
}

void GameLogic::DeletePlayer( int playerId )
{
	if ( m_PlayerList[playerId] != nullptr )
	{
		delete m_PlayerList[playerId];
	}
}

bool GameLogic::IsValidId( int playerId )
{
	return ( m_PlayerList[playerId] != nullptr ) ? true : false;
}

void GameLogic::Update()
{
	DWORD currentTime = timeGetTime();
	float dt = ( static_cast<float>( currentTime - m_PrevTime ) ) / 1000.f;
	m_PrevTime = currentTime;

	for ( unsigned int playerId = 0; playerId < MAX_PLAYER_NUM; ++playerId )
	{
		if ( m_PlayerList[playerId] != nullptr )
		{
			m_PlayerList[playerId]->update( dt );
		}
	}
}

bool GameLogic::SetPosition( unsigned int playerId, float x, float y, float z )
{ 
	if ( IsValidId( playerId ) )
	{
		m_PlayerList[playerId]->SetPosition( x, y, z );

		return true;
	}

	return false;
}

bool GameLogic::SetScale( unsigned int playerId, float scaleX, float scaleY, float scaleZ )
{ 
	if ( IsValidId( playerId ) )
	{
		m_PlayerList[playerId]->SetScale( scaleX, scaleY, scaleZ );

		return true;
	}
	m_PlayerList[playerId]->SetScale( scaleX, scaleY, scaleZ );

	return false;
}

bool GameLogic::SetRotation( unsigned int playerId, float rotationX, float rotationY, float rotationZ )
{ 
	if ( IsValidId( playerId ) )
	{
		m_PlayerList[playerId]->SetRotation( rotationX, rotationY, rotationZ );

		return true;
	}

	return false;
}

bool GameLogic::SetAcceleration( unsigned int playerId )
{ 
	if ( IsValidId( playerId ) )
	{
		m_PlayerList[playerId]->SetAcceleration();

		return true;
	}

	return false;
}

bool GameLogic::Stop( unsigned int playerId )
{ 
	if ( IsValidId( playerId ) )
	{
		m_PlayerList[playerId]->Stop();

		return true;
	}

	return false;
}

bool GameLogic::RotateDicrection( unsigned int playerId, float y, float x )
{
	if ( IsValidId( playerId ) )
	{
		m_PlayerList[playerId]->RotateDicrection( y, x );

		return true;
	}

	return false;
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