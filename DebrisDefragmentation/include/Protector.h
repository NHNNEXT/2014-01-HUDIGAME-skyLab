#pragma once
#include "ClassComponent.h"
class Protector :
	public ClassComponent
{
public:
	Protector();
	virtual ~Protector();

	bool UseSkill( ClassSkill skill, int id, const D3DXVECTOR3& direction );

	CREATE_FUNC( Protector );

private:
	bool SkillWarning( int id, const D3DXVECTOR3& direction );
	bool SkillShareOxygen( int id, const D3DXVECTOR3& direction );
	bool SkillEMP( int id, const D3DXVECTOR3& direction );

	virtual void DoPeriodWork( float dTime );
};

