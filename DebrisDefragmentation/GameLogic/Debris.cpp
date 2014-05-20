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
	// 충돌 박스 초기화

	m_Transform.SetPosition( 
		((rand() % 2000) - 1000) / 20.0f,
		((rand() % 2000) - 1000) / 20.0f,
		((rand() % 2000) - 1000) / 20.0f 
		);

	m_CollisionBox.SetCenterPosition( ZERO_VECTOR3 );
	m_CollisionBox.SetLength( DEBRIS_AXIS_LEN );
	m_CollisionBox.InitAxisDir();
	m_CollisionBox.InitPointList();
	m_CollisionBox.InitRadius();
}
