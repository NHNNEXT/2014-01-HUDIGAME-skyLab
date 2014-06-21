#pragma once

#include "DDModel.h"
#include "rigidbody.h"
#include "CollisionBox.h"
#include "ISSModule.h"

class ObjectISS :
	public ClientObject
{
public:
	ObjectISS();
	ObjectISS( std::wstring modelPath );
	virtual ~ObjectISS();

	void Init();
	void SetVelocity( DDVECTOR3 val ) { m_RigidBody.m_Velocity = val; }
	void SetOwner( int moduleIdx, int color );
	void SetHP( int moduleIdx, float hp );

	CREATE_OBJECT( ObjectISS );

private:
	virtual void RenderItSelf( );
	virtual void UpdateItSelf( float dTime );

	void InitCollisionBox( );
	void DrawCollisionBox( const CollisionBox* box );

	DDModel*		m_CharacterModel = nullptr;

	Rigidbody m_RigidBody;			// rigidbody 자체 초기화
	std::array<ISSModule, MODULE_NUMBER> m_ModuleList;
};
