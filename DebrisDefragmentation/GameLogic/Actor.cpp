#include "stdafx.h"
#include "Actor.h"
#include "Striker.h"
#include "Engineer.h"
#include "Protector.h"

#include "Physics.h"
#include "GameOption.h"

Actor::Actor( CharacterClass actorClass )
{
	// 조심해!!
	// 팩토리 하나 만들어야 될 듯
	switch ( actorClass )
	{
	case CharacterClass::STRIKER:
		m_CharacterClass = Striker::Create( );
		break;
	case CharacterClass::ENGINEER:
		m_CharacterClass = Engineer::Create( );
		break;
	case CharacterClass::PROTECTOR:
		m_CharacterClass = Protector::Create( );
		break;
	default:
		assert( false );
		break;
	}
}


Actor::~Actor()
{
}

void Actor::IncreaseVelocity( const D3DXVECTOR3 &deltaVelocity )
{
	m_CharacterClass->SetVelocity( m_CharacterClass->GetVelocity() + deltaVelocity );
}

void Actor::SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity )
{ 
	m_CharacterClass->SetSpin( rotationAxis, angularVelocity); 
	m_CharacterClass->SetSpinTime( 0.0f );
	m_CharacterClass->SetSpinnigFlag( true );
}

void Actor::AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity ) 
{ 
	m_CharacterClass->AddSpin( rotationAxis, angularVelocity); 
	// m_SpinTime = 0.0f;
	m_CharacterClass->SetSpinnigFlag( true );
}

void Actor::StopSpin( ) 
{ 
	m_CharacterClass->SetSpinnigFlag( false );
	m_CharacterClass->SetSpinTime( 0.0f );
	m_CharacterClass->StopSpin(); 
}


void Actor::InitTeamPosition()
{
	switch ( GetClassComponent().GetTeam() )
	{
		case TeamColor::RED:
			GetTransform().SetPosition( RED_TEAM_POSITION );
			GetTransform().SetRotation( RED_TEAM_ROTATION );
			break;
		case TeamColor::BLUE:
			GetTransform().SetPosition( BLUE_TEAM_POSITION );
			GetTransform().SetRotation( BLUE_TEAM_ROTATION );
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