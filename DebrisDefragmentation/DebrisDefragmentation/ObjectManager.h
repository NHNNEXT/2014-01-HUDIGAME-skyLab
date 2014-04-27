#pragma once
#include "ISS.h"

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	// ISS�� �ڽ��� ��ǥ�踦 ���� ��ǥ��� �����ϰ� ����ϹǷ� �ڽ��� m_Pos�� �ٷ� ���� ����
	DDVECTOR3 GetIssPosition() { return m_Iss.GetPosition(); }

private:
	ISS m_Iss;
};

extern ObjectManager* GObjectManager;