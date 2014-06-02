#include "stdafx.h"
#include "SpaceMineModel.h"

SpaceMineModel::SpaceMineModel()
{
}

SpaceMineModel::~SpaceMineModel()
{
}

void SpaceMineModel::Init( unsigned int id, TeamColor color, float issPos )
{
	m_Id = id;
	m_TeamColor = color;
	m_FirstIssPos = issPos;
}