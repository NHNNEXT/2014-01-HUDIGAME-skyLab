#pragma once
#include "DDModel.h"
class CharacterModel :
	public DDModel
{
public:
	CharacterModel();
	CharacterModel( std::wstring modelPath );
	virtual ~CharacterModel();

	CREATE_OBJECT_WSTRING( CharacterModel, modelPath );
	
private:
	virtual void UpdateItSelf( float dTime );
};

