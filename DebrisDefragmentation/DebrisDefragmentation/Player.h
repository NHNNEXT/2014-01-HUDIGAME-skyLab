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
	void Init();
	
	void Update( float dTime );
	void UpdateItSelf( float dTime );

private:
	DDCamera*	m_Camera;
	Character*	m_Character;
};

