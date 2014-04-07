#include "PlayScene.h"


PlayScene::PlayScene()
{
	// init objects
	m_pDirectonalLight = DDLight::Create();
	m_pPlayer = Player::Create();

	AddChild( m_pDirectonalLight );
	AddChild( m_pPlayer );

}


PlayScene::~PlayScene()
{
}

void PlayScene::Render()
{
	DDObject::Render();
}

void PlayScene::Update( float dTime )
{
	DDObject::Update( dTime );
}
