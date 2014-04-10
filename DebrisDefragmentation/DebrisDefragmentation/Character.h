#pragma once
#include "DDModel.h"
class Character :
	public DDModel
{
public:
	Character();
	Character( wchar_t* modelPath );
	virtual ~Character();

	static Character* Create(wchar_t* modelPath);


private:
	virtual void UpdateItSelf( float dTime );
	float tmpTimeCounter;
};

