#pragma once
#include "DDScene.h"
#include "DDConfig.h"
#include "DDLight.h"
#include "Player.h"

class PlayScene :
	public DDScene
{
public:
	PlayScene();
	virtual ~PlayScene();

	CREATE_FUNC( PlayScene );

	virtual void Render();
	virtual void Update( float dTime );

private:
	DDLight*	m_pDirectonalLight;
	Player*		m_pPlayer;

};

