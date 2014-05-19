#pragma once
#include "Actor.h"

class Dispenser : public Actor
{
public:
	Dispenser();
	~Dispenser();

private :
	virtual void UpdateItSelf( float dTime );
};

