#pragma once
#include "DDObject.h"
#include "DDCamera.h"
#include "Character.h"

class Player :
	public DDObject
{
public:
	Player();
	virtual ~Player();

	CREATE_FUNC( Player );

	virtual void Render();
	virtual void Update( float dTime );

private:
	DDCamera*	m_Camera;
	Character*	m_Character;
};

