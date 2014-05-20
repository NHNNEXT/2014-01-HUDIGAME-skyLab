#include "stdafx.h"
#include "Actor.h"
#include "Striker.h"
#include "Engineer.h"
#include "Protector.h"

#include "Physics.h"
#include "GameOption.h"

Actor::Actor( CharacterClass actorClass )
{
	m_CharacterClass = ClassComponent::Create( actorClass );
}

Actor::~Actor()
{
}

void Actor::IncreaseVelocity( const D3DXVECTOR3 &deltaVelocity )
{
	m_CharacterClass->SetVelocity( m_CharacterClass->GetVelocity() + deltaVelocity );
}

void Actor::InitTeamPosition()
{
	switch ( GetClassComponent()->GetTeam() )
	{
		case TeamColor::RED:
			GetTransform()->SetPosition( RED_TEAM_POSITION );
			GetTransform()->SetRotation( RED_TEAM_ROTATION );
			break;
		case TeamColor::BLUE:
			GetTransform()->SetPosition( BLUE_TEAM_POSITION );
			GetTransform()->SetRotation( BLUE_TEAM_ROTATION );
			break;
		default:
			break;
	}
}

void Actor::GoForward() 
{ 
	m_CharacterClass->GoForward( GetViewDirection() ); 
}

void Actor::Stop() 
{ 
	m_CharacterClass->Stop(); 
}

void Actor::TurnBody( float x, float y, float z ) 
{ 
	m_CharacterClass->TurnBody( m_Transform, x, y, z ); 
}