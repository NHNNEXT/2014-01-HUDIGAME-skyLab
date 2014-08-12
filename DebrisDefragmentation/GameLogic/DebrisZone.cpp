#include "stdafx.h"
#include "DebrisZone.h"
#include "Debris.h"
#include "DebrisManager.h"

DebrisZone::DebrisZone()
{
}


DebrisZone::~DebrisZone()
{
}

void DebrisZone::Init( int id )
{
	if ( !m_DebrisList.empty() )
	{
		for ( auto it = m_DebrisList.begin(); it != m_DebrisList.end(); )
			delete it->second;

		m_DebrisList.clear();
	}

	for ( int i = 0; i < DEBRIS_COUNT_IN_EACH_ZONE; ++i )
	{
		Debris* newDebris = new Debris();
		newDebris->SetZoneId( m_ZoneId );

		m_DebrisList.insert( std::map<int, Debris*>::value_type( m_ZoneId * DEBRIS_COUNT_IN_EACH_ZONE + i, newDebris ) );
	}
}

void DebrisZone::AddDebris( int key, Debris* debris )
{
	m_DebrisList.insert( std::map<int, Debris*>::value_type( key, debris ) );
}

void DebrisZone::RemoveDebris( int key )
{
	m_DebrisList.erase( key );
}

Debris* DebrisZone::GetDebris( int key )
{
	std::map<int, Debris*>::iterator iter = m_DebrisList.find( key );

	if ( iter != m_DebrisList.end() )
		return iter->second;
	
	return nullptr;
}

void DebrisZone::Update( float dt )
{
	// 이동하는 로직 처리
	// 위치 확인
	// 존 이동
	for ( auto it = m_DebrisList.begin(); it != m_DebrisList.end(); )
	{
		Debris* debris = it->second;
		debris->Update( dt );
		
		int newZone = debris->CalculateZoneId();
		if ( newZone != debris->GetZoneId() )
		{
			GDebrisManager->ChangeDebrisZone( debris, debris->GetZoneId(), newZone );
		}
	}
}