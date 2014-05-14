#pragma once
#include "ClassComponent.h"
class Striker :
	public ClassComponent
{
public:
	Striker();
	virtual ~Striker();

	bool UseSkill( ClassSkill skill, int id, const D3DXVECTOR3& direction );

	bool SkillPull( int id, const D3DXVECTOR3& direction );
	bool SkillSetMine( int id, const D3DXVECTOR3& direction );
	bool SkillMoveFast( int id, const D3DXVECTOR3& direction );

	CREATE_FUNC( Striker );
};

