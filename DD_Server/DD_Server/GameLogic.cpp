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
	///# 이 코드 뭔가효?
	for ( unsigned int playerId = 0; playerId < MAX_PLAYER_NUM; ++playerId )
	{
		///# 여러번 불릴 수 있다는 이야기?
		if ( m_PlayerList[playerId] == nullptr )
		{
			///# 매번 0번 객체만 리턴하는데? for 루프가 의미가 없음.
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
		///# 지운 다음에는 반드시 nullptr 대입.
		delete m_PlayerList[playerId];
	}
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
	///# 배열 범위 체크 항상 할 것.
	m_PlayerList[playerId]->SetPosition( x, y, z ); 

	return true;
}

bool GameLogic::SetScale( unsigned int playerId, float scaleX, float scaleY, float scaleZ )
{ 
	///# 배열 범위 체크 항상 할 것.
	m_PlayerList[playerId]->SetScale( scaleX, scaleY, scaleZ );

	return true;
}

bool GameLogic::SetRotation( unsigned int playerId, float rotationX, float rotationY, float rotationZ )
{ 
	///# 근데 꼭 이렇게 전지 전능한 GameLogic을 통해서 해야되는가? 
	m_PlayerList[playerId]->SetRotation( rotationX, rotationY, rotationZ );

	return true;
}

bool GameLogic::SetAcceleration( unsigned int playerId )
{ 
	m_PlayerList[playerId]->SetAcceleration( );

	return true;
}

bool GameLogic::Stop( unsigned int playerId )
{ 
	m_PlayerList[playerId]->Stop( );

	return true;
}

bool GameLogic::RotateDicrection( unsigned int playerId, float y, float x )
{
	m_PlayerList[playerId]->RotateDicrection( y, x );

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