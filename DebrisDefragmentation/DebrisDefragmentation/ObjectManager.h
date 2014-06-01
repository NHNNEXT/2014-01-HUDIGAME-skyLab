#pragma once

#include "GameOption.h"
#include "ObjectISS.h"

class DebrisModel;
class DispenserModel;
class SpaceMineModel;

class ObjectManager
{
public:
	ObjectManager();

	~ObjectManager();

	// ObjectISS는 자신의 좌표계를 월드 좌표계와 동일하게 사용하므로 자신의 m_Pos를 바로 리턴 가능
	DDVECTOR3 GetObjectISSPosition() { return m_ObjectISS->GetTransform().GetPosition(); }
	int GetRandomSeed() const { return RandomSeed; }
	void SetRandomSeed( int val ) { RandomSeed = val; }
	void AddResourceDebris( int index, DebrisModel* dm ) { m_ResourceDebrisList[index] = dm; }
	DebrisModel* GetResourceDebris( int index ) { return m_ResourceDebrisList[index]; }
	void SetResourceDebris( int index, DebrisModel* dm ) { m_ResourceDebrisList[index] = dm; }

	void AddDispenserModel( DispenserModel* dispenserModel ) { m_DispenserModelList.push_back( dispenserModel ); }
	void RegisterObjectISS( ObjectISS* iss ) { m_ObjectISS = iss; }
	ObjectISS* GetISS() { return m_ObjectISS; }

	void RegisgerSpaceMine( unsigned int spaceMineId, const D3DXVECTOR3& position, const D3DXVECTOR3& direction, TeamColor team );
	void DeregisterSpaceMine( unsigned int spaceMineId );

	void UpdateObjects();

private:
	ObjectISS* m_ObjectISS = nullptr;
	std::list<DispenserModel*> m_DispenserModelList;
	std::array<DebrisModel*, RESOURCE_DEBRIS_NUMBER> m_ResourceDebrisList;
	int RandomSeed = 0;
	
	std::map<unsigned int, SpaceMineModel*> m_SpaceMineList;
};

extern ObjectManager* GObjectManager;