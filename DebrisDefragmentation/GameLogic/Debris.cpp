#include "stdafx.h"
#include "Debris.h"


Debris::Debris()
{
}


Debris::~Debris()
{
}

void Debris::Init()
{
	// �浹 �ڽ� �ʱ�ȭ

	m_Transform.SetPosition( 
		( ( rand() % DEBRIS_SPREAD_RANGE ) - ( DEBRIS_SPREAD_RANGE >> 1 ) ),
		( ( rand() % DEBRIS_SPREAD_RANGE ) - ( DEBRIS_SPREAD_RANGE >> 1 ) ),
		( ( rand() % DEBRIS_SPREAD_RANGE ) - ( DEBRIS_SPREAD_RANGE >> 1 ) )
		);

	m_CollisionBox.SetCenterPosition( ZERO_VECTOR3 );
	m_CollisionBox.SetLength( DEBRIS_AXIS_LEN );
	m_CollisionBox.InitAxisDir();
	m_CollisionBox.InitPointList();
	m_CollisionBox.InitRadius();
	m_Matrix = m_Transform.MatrixTransform();
}
