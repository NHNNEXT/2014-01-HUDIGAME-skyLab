#include "stdafx.h"
#include "Character.h"
#include "DDRenderer.h"
#include "DDApplication.h"


Character::Character()
{
}

Character::Character( wchar_t* modelPath ) : DDModel(modelPath)
{
}


Character::~Character()
{
}

Character* Character::Create( wchar_t* modelPath )
{
	Character* pInstance = new Character( modelPath );
	return pInstance;
}

void Character::UpdateItSelf( float dTime )
{
	UNREFERENCED_PARAMETER(dTime);
}
