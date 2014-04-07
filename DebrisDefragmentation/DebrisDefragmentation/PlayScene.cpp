#include "PlayScene.h"


PlayScene::PlayScene()
{
}


PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	// init objects
	m_pDirectonalLight = DDLight::Create();

	m_pPlayer = Player::Create();
	m_pPlayer->Init();

	AddChild( m_pDirectonalLight );
	AddChild( m_pPlayer );
}