#pragma once
#include "DDScene.h"

class DDLight;
class Player;

class PlayScene :
	public DDScene
{
public:
	PlayScene();
	PlayScene( std::wstring sceneName );
	virtual ~PlayScene();
		
	static PlayScene* Create( std::wstring sceneName );
	CREATE_FUNC( PlayScene );

	void Init();


private:
	virtual void UpdateItSelf( float dTime );
	void HideMousePointer();

	DDLight*	m_pDirectonalLight;
	Player*		m_pPlayer;

	DDPoint		m_PrevMousePosition;
};

