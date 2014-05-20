#pragma once
#include "Actor.h"
class Debris :
	public Actor
{
public:
	void Init();

	Debris();
	virtual ~Debris();

private:
	//virtual void UpdateItSelf( float dTime );
};

