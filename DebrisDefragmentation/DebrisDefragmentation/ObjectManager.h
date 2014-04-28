#pragma once
#include "ISS.h"

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	// ISS는 자신의 좌표계를 월드 좌표계와 동일하게 사용하므로 자신의 m_Pos를 바로 리턴 가능
	DDVECTOR3 GetIssPosition() { return m_Iss.GetPosition(); }

private:
	ISS m_Iss;
};

extern ObjectManager* GObjectManager;