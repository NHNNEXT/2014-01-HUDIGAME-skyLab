#pragma once
#include "ObjectISS.h"

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	// ObjectISS는 자신의 좌표계를 월드 좌표계와 동일하게 사용하므로 자신의 m_Pos를 바로 리턴 가능
	DDVECTOR3 GetObjectISSPosition() { return m_ObjectISS->GetTransform().GetPosition(); }

	void RegisterObjectISS( ObjectISS* iss ) { m_ObjectISS = iss; }
	ObjectISS* GetISS() { return m_ObjectISS; }

private:
	ObjectISS* m_ObjectISS = nullptr;
};

extern ObjectManager* GObjectManager;