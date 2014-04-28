#include "stdafx.h"
#include "Actor.h"
#include "Physics.h"
#include "GameConfig.h"

Actor::Actor()
{
	m_CharacterClass = ClassComponent::Create();	
}


Actor::~Actor()
{
}


void Actor::SetAccelerarion( const D3DXVECTOR3 &direction )
{
	m_CharacterClass->SetAccelerationStartTime( timeGetTime() );
	m_CharacterClass->SetIsAccelerating( true );

	m_RigidBody.m_Acceleration += ( direction * ACCELERATION_WEIGHT );
}

void Actor::IncreaseVelocity( const D3DXVECTOR3 &deltaVelocity )
{
	m_RigidBody.m_Velocity += deltaVelocity;
}

void Actor::SetSpin( D3DXVECTOR3 rotationAxis, float angularVelocity )
{ 
	m_CharacterClass->SetSpin( rotationAxis, angularVelocity, m_RigidBody ); 
	m_CharacterClass->SetSpinTime( 0.0f );
	m_CharacterClass->SetSpinnigFlag( true );
}

void Actor::AddSpin( D3DXVECTOR3 rotationAxis, float angularVelocity ) 
{ 
	m_CharacterClass->AddSpin( rotationAxis, angularVelocity, m_RigidBody ); 
	// m_SpinTime = 0.0f;
	m_CharacterClass->SetSpinnigFlag( true );
}

void Actor::StopSpin( ) 
{ 
	m_CharacterClass->SetSpinnigFlag( false );
	m_CharacterClass->SetSpinTime( 0.0f );
	m_CharacterClass->StopSpin( m_RigidBody ); 
}