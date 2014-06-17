#include "stdafx.h"
#include "ObjectManager.h"
#include "DebrisModel.h"
#include "DispenserModel.h"
#include "SpaceMineModel.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include "EnvironmentManager.h"

ObjectManager* GObjectManager = nullptr;

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::InstallStructure( unsigned int structureId, StructureType structureType, const D3DXVECTOR3& position, const D3DXVECTOR3& direction, TeamColor team )
{
	switch ( structureType )
	{
	case StructureType::DISPENSER:
		RegisgerDispenser( structureId, position, direction, team );
		break;
	case StructureType::SHELTER:
		break;
	case StructureType::SPACE_MINE:
		RegisgerSpaceMine( structureId, position, direction, team );
		break;
	default:
		break;
	}
}

void ObjectManager::UninstallStructure( unsigned int structureId, StructureType structureType )
{
	switch ( structureType )
	{
	case StructureType::DISPENSER:
		DeregisterDispenser( structureId );
		break;
	case StructureType::SHELTER:
		break;
	case StructureType::SPACE_MINE:
		DeregisterSpaceMine( structureId );
		break;
	default:
		break;
	}
}

void ObjectManager::RegisgerDispenser( unsigned int dispenserId, const D3DXVECTOR3& position, const D3DXVECTOR3& direction, TeamColor team )
{
	DispenserModel* newDispenser = DispenserModel::Create();
	newDispenser->Init( dispenserId, team, m_ObjectISS->GetTransform().GetPositionZ() );

	newDispenser->SetModelMesh( GSceneManager->GetScene()->GetModelPool().GetModel( ModelType::DISPENSER ) );
	newDispenser->GetTransform().SetPosition( position - m_ObjectISS->GetTransform().GetPosition() );
	newDispenser->GetTransform().SetRotation( direction );
	newDispenser->GetTransform().SetScale( DISPENSER_SCALE );

	m_DispenserList.insert( std::map<unsigned int, DispenserModel*>::value_type( dispenserId, newDispenser ) );

	// 그릴 수 있게 ISS에 추가
	assert( m_ObjectISS );
	m_ObjectISS->AddChild( newDispenser );
}

void ObjectManager::DeregisterDispenser( unsigned int dispenserId )
{
	std::map<unsigned int, DispenserModel*>::iterator it = m_DispenserList.find( dispenserId );
	assert( it != m_DispenserList.end() );
	
	//effect 재생
	GEnvironmentManager->PlayParticleEffect( EffectType::EXPLOSION, ( it->second )->GetTransform().GetPosition() );
	// 등록한 ISS에서 지우자
	// delete it->second;
	assert( m_ObjectISS );
	m_ObjectISS->RemoveChild( it->second );

	m_DispenserList.erase( dispenserId );
}

void ObjectManager::RegisgerSpaceMine( unsigned int spaceMineId, const D3DXVECTOR3& position, const D3DXVECTOR3& direction, TeamColor team )
{
	SpaceMineModel* newMine = SpaceMineModel::Create();
	newMine->Init( spaceMineId, team, m_ObjectISS->GetTransform().GetPositionZ() );

	newMine->SetModelMesh( GSceneManager->GetScene()->GetModelPool().GetModel( ModelType::SPACE_MINE ) );
	newMine->GetTransform().SetPosition( position - m_ObjectISS->GetTransform().GetPosition() );
	newMine->GetTransform().SetRotation( direction );
	newMine->GetTransform().SetScale( SPACE_MINE_SCALE );

	m_SpaceMineList.insert( std::map<unsigned int, SpaceMineModel*>::value_type( spaceMineId, newMine ) );

	// 그릴 수 있게 ISS에 추가
	assert( m_ObjectISS );
	m_ObjectISS->AddChild( newMine );
}

void ObjectManager::DeregisterSpaceMine( unsigned int spaceMineId )
{
	std::map<unsigned int, SpaceMineModel*>::iterator it = m_SpaceMineList.find( spaceMineId );
	assert( it != m_SpaceMineList.end() );

	//effect 재생
	GEnvironmentManager->PlayParticleEffect( EffectType::EXPLOSION, ( it->second )->GetTransform().GetPosition() );

	// 등록한 ISS에서 지우자
	// delete it->second;
	assert( m_ObjectISS );
	m_ObjectISS->RemoveChild( it->second );

	m_SpaceMineList.erase( spaceMineId );
}

void ObjectManager::UpdateObjects()
{
	
}
