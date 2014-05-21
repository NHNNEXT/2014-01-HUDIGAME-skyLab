#pragma once
#include "Actor.h"

class Dispenser : public Actor
{
public:
	Dispenser();
	virtual ~Dispenser();

private :
	virtual void UpdateItSelf( float dTime );
};

