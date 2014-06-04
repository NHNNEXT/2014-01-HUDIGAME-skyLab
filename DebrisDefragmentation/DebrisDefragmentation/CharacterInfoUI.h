#pragma once

#include "DDUIModule.h"

class CharacterInfoUI :
	public DDUIModule
{
public:
	CharacterInfoUI();
	virtual ~CharacterInfoUI();

	bool GenerateUI();

	void Update( float dt );
};

