#include "stdafx.h"
#include "DDBillboardEffect.h"
#include "SceneManager.h"
#include "PlayScene.h"

DDBillboardEffect::DDBillboardEffect()
{
}


DDBillboardEffect::~DDBillboardEffect()
{
}

void DDBillboardEffect::Init()
{
	MeshInfo* mi = GSceneManager->GetScene()->GetModelPool().GetModel( ModelType::PUSHPULL_EFFECT );
	for ( auto eachPlane : m_Billboard )
	{
		eachPlane = DDModel::Create();
		eachPlane->SetModelMesh( mi );
		AddChild( eachPlane );
	}
}
