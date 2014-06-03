#pragma once
#include "DDUI.h"
class CharacterStateUI :
	public DDUI
{
public:
	CharacterStateUI();
	virtual ~CharacterStateUI();

	void Init();

	CREATE_OBJECT( CharacterStateUI );

private:
	virtual void UpdateItSelf( float dTime );
	virtual void RenderItSelf();
};

