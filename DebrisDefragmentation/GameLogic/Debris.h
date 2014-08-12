#pragma once
#include "Actor.h"
class Debris :
	public Actor
{
public:
	void Init();

	Debris();
	virtual ~Debris();

	int CalculateZoneId();
	int GetZoneId() { return m_ZoneId; }
	void SetZoneId( int id ) { m_ZoneId = id; }

private:
	// virtual void UpdateItSelf( float dTime );
	int m_ZoneId = -1;
};

