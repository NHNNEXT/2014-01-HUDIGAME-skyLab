#pragma once
#include "DDModel.h"
class CharacterModel :
	public DDModel
{
public:
	CharacterModel();
	//CharacterModel( std::wstring modelPath );
	virtual ~CharacterModel();

	//CREATE_OBJECT_WSTRING( CharacterModel, modelPath );
	CREATE_OBJECT( CharacterModel );
	
private:
	virtual void UpdateItSelf( float dTime );
};

