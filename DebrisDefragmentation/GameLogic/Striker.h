#pragma once
#include "ClassComponent.h"
class Striker :
	public ClassComponent
{
public:
	Striker();
	virtual ~Striker();

	bool UseSkill( ClassSkill skill, int id, const D3DXVECTOR3& direction );

	CREATE_FUNC( Striker );

private:
	bool SkillPull( int id, const D3DXVECTOR3& direction );
	bool SkillSetMine( int id, const D3DXVECTOR3& direction );
	bool SkillMoveFast( int id, const D3DXVECTOR3& direction );

	virtual void DoPeriodWork( float dTime );

	float	m_RemainFastMove = 0.0f;
	int		m_FastMoveTarget = -1;
};

