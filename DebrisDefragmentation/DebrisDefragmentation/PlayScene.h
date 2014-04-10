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

	void Init();


private:
	virtual void UpdateItSelf( float dTime );
	void HideMousePointer();

	DDLight*	m_pDirectonalLight;
	Player*		m_pPlayer;

	DDPoint		m_PrevMousePosition;
};

