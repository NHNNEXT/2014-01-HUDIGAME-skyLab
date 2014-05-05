#pragma once

#include "DDObject.h"
#include "DDModel.h"
#include "rigidbody.h"
#include "CollisionBox.h"
#include "ISSModule.h"

class ObjectISS :
	public DDObject
{
public:
	ObjectISS();
	ObjectISS( std::wstring modelPath );
	virtual ~ObjectISS();

	void Init();

	CREATE_OBJECT( ObjectISS );

private:
	virtual void RenderItSelf( );
	virtual void UpdateItSelf( float dTime );

	void InitCollisionBox( );
	void DrawModuleCollisionBox( ISSModule & module );

	DDModel*		m_CharacterModel = nullptr;

	Rigidbody m_RigidBody;			// rigidbody 자체 초기화
	std::array<ISSModule, MODULE_NUMBER> m_ModuleList;
};
