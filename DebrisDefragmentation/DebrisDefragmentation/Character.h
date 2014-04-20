#pragma once
#include "DDModel.h"
class Character :
	public DDModel
{
public:
	Character();
	Character( std::wstring modelPath );
	virtual ~Character();

	CREATE_FUNC_WSTRING( Character, modelPath );

	//static Character* Create(wchar_t* modelPath);


private:
	virtual void UpdateItSelf( float dTime );
};

