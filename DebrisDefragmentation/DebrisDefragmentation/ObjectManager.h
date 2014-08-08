#pragma once

#include "GameOption.h"

class DebrisModel;
class DispenserModel;
class SpaceMineModel;

class ObjectManager
{
public:
	ObjectManager();

	~ObjectManager();

	// ObjectISS는 자신의 좌표계를 월드 좌표계와 동일하게 사용하므로 자신의 m_Pos를 바로 리턴 가능
	int GetRandomSeed() const { return m_RandomSeed; }
	void SetRandomSeed( int val ) { m_RandomSeed = val; }
	void AddResourceDebris( int index, DebrisModel* dm ) { m_ResourceDebrisList[index] = dm; }
	DebrisModel* GetResourceDebris( int index ) { return m_ResourceDebrisList[index]; }
	void SetResourceDebris( int index, DebrisModel* dm ) { m_ResourceDebrisList[index] = dm; }

	void UpdateObjects();

private:
	int m_RandomSeed = 0;

	std::array<DebrisModel*, RESOURCE_DEBRIS_NUMBER> m_ResourceDebrisList;
};

extern ObjectManager* GObjectManager;