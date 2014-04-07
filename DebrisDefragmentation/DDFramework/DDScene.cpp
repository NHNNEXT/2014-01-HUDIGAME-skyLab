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
	DDObject::Render();
}

void DDScene::Update( float dTime )
{
	DDObject::Update( dTime );
}

KeyState DDScene::GetKeyState( int key )
{
	return DDInputSystem::GetInstance()->GetKeyState( key );
}

DDPoint DDScene::GetMousePosition()
{
	return DDInputSystem::GetInstance( )->GetMousePosition( );
}