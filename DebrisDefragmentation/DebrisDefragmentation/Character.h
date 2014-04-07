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

	virtual void Render();
	virtual void Update( float dTime );
};

