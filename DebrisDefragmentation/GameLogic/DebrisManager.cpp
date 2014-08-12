#include "stdafx.h"
#include "DebrisManager.h"
#include "DebrisZone.h"
#include "Debris.h"

DebrisManager* GDebrisManager = nullptr;

DebrisManager::DebrisManager()
{
	m_DebrisZoneList.fill( nullptr );
}


DebrisManager::~DebrisManager()
{
}

void DebrisManager::Init()
{
	// debris zone 초기화
	for ( int i = 0; i < DEBRIS_ZONE_NUMBER; ++i )
	{
		if ( m_DebrisZoneList[i] == nullptr )
			m_DebrisZoneList[i] = new DebrisZone();

		m_DebrisZoneList[i]->Init( i );
	}
}

void DebrisManager::Update( float dt )
{
	for ( int i = 0; i < DEBRIS_ZONE_NUMBER; ++i )
	{
		m_DebrisZoneList[i]->Update( dt );
	}
}

void DebrisManager::ChangeDebrisZone( Debris* debris, int prevZone, int newZone )
{
	// 모아놨다가 한 번에 처리???
}