#include "stdafx.h"
#include "ObjectManager.h"
#include "DebrisModel.h"
#include "SpaceMineModel.h"
#include "SceneManager.h"
#include "PlayScene.h"

ObjectManager* GObjectManager = nullptr;

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::RegisgerSpaceMine( unsigned int spaceMineId, const D3DXVECTOR3& position, const D3DXVECTOR3& direction, TeamColor team )
{
	SpaceMineModel* newMine = new SpaceMineModel( spaceMineId, team, m_ObjectISS->GetTransform().GetPositionZ() );

	newMine->SetModelMesh( GSceneManager->GetScene()->GetModelPool().GetModel( ModelType::SPACE_MINE ) );
	newMine->GetTransform().SetPosition( position );
	newMine->GetTransform().SetRotation( direction );
	newMine->GetTransform().SetScale( SPACE_MINE_SCALE );

	m_SpaceMineList.insert( std::map<unsigned int, SpaceMineModel*>::value_type( spaceMineId, newMine ) );

	// 그릴 수 있게 ISS에 추가
	assert( m_ObjectISS );
	m_ObjectISS->AddChild( newMine );
}

void ObjectManager::DeregisterSpaceMine( unsigned int spaceMineId )
{
	std::map<unsigned, SpaceMineModel*>::iterator it = m_SpaceMineList.find( spaceMineId );
	assert( it != m_SpaceMineList.end() );

	// 등록한 ISS에서 지우자
	// delete it->second;
	assert( m_ObjectISS );
	m_ObjectISS->RemoveChild( it->second );

	m_SpaceMineList.erase( spaceMineId );
}

void ObjectManager::UpdateObjects()
{
	// 애들 위치 업데이트 하자
	float IssPos = m_ObjectISS->GetTransform().GetPositionZ();
	for ( std::map<unsigned, SpaceMineModel*>::const_iterator it = m_SpaceMineList.begin(); it != m_SpaceMineList.end(); ++it )
	{
		it->second->UpdateIssPosition( IssPos );
	}
}