#pragma once
#include "ClassComponent.h"
class Engineer :
	public ClassComponent
{
public:
	Engineer();
	virtual ~Engineer();

	bool UseSkill( ClassSkill skill, int id, const D3DXVECTOR3& direction );

	CREATE_FUNC( Engineer );

private:
	bool SkillGather( int id, const D3DXVECTOR3& direction );
	bool SkillShelter( int id, const D3DXVECTOR3& direction );
	bool SkillDispenser( int id, const D3DXVECTOR3& direction );

	bool DebrisInRay( const D3DXVECTOR3 &viewDirection, const D3DXVECTOR3 &startPoint );

	virtual void DoPeriodWork( float dTime );
};

