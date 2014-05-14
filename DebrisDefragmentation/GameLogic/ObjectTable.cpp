#include "stdafx.h"
#include "ObjectTable.h"

ObjectTable* GObjectTable = nullptr;

ObjectTable::~ObjectTable()
{
}

void ObjectTable::Init( ActorManager* actorManager ) 
{ 
	m_ActorManager = actorManager; 

	m_CharacterList.fill( nullptr );
}