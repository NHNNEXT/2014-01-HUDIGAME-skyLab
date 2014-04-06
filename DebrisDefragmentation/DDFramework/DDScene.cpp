#include "stdafx.h"
#include "DDScene.h"


DDScene::DDScene()
{
}


DDScene::~DDScene()
{
}

DDScene* DDScene::Create()
{
	DDScene* pInstance = new DDScene();
	return pInstance;
}

void DDScene::Render()
{	
	RenderChildNodes();
}

void DDScene::Update( float dTime )
{
	UpdateChildNodes( dTime );
}
