#pragma once
#include "DDModel.h"
class CharacterModel :
	public DDModel
{
public:
	CharacterModel();	
	virtual ~CharacterModel();
		
	CREATE_OBJECT( CharacterModel );
	virtual void SetupFX();
	
private:
	virtual void UpdateItSelf( float dTime );
};

