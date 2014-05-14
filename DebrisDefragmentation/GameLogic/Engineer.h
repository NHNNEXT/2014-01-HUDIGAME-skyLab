﻿#pragma once
#include "ClassComponent.h"
class Engineer :
	public ClassComponent
{
public:
	Engineer();
	virtual ~Engineer();

	bool UseSkill( ClassSkill skill, int id, const D3DXVECTOR3& direction );

	bool SkillGather( int id, const D3DXVECTOR3& direction );
	bool SkillSentryGun( int id, const D3DXVECTOR3& direction );
	bool SkillDespenser( int id, const D3DXVECTOR3& direction );

	CREATE_FUNC( Engineer );
};

