#pragma once
#include "ClientObject.h"
#include "Environment.h"
#include "DDModel.h"

class DDBillboardEffect : public ClientObject
{
public:
	DDBillboardEffect();
	virtual ~DDBillboardEffect();
	CREATE_OBJECT( DDBillboardEffect );

	void Init();

private:
	std::array<DDModel*, BILLBOARD_RESOLUTION> m_Billboard;
};

