#include "stdafx.h"
#include "DispenserModel.h"

DispenserModel::DispenserModel()
{
}

DispenserModel::~DispenserModel()
{
}

void DispenserModel::Init( unsigned int id, TeamColor color, float issPos )
{
	m_Id = id;
	m_TeamColor = color;
	m_FirstIssPos = issPos;
}