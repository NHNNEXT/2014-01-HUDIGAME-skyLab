#pragma once

#include "GameOption.h"

class Debris;

class DebrisZone
{
public:
	DebrisZone();
	~DebrisZone();

	void Init( int id );

	void AddDebris( int key, Debris* debris );
	void RemoveDebris( int key );

	Debris* GetDebris( int key );

	void Update( float dt );

private:
	int m_ZoneId = -1;
	std::map<int, Debris*> m_DebrisList;
};

