/*
	ISS자체
	자신을 이루는 모듈들을 arrary로 가지고 있다.
	주기적으로 각각의 모듈을 점령하고 있는 팀의 수에 따라서 움직인다.
*/

#pragma once

#include "ISSModule.h"

class ISS
{
public:
	ISS();
	~ISS();

	void Init();
	void Update( float dTime );
	float GetPosition() { return m_CurrentPos; }
	float GetVelocity() { return m_Velocity; }
	
	ISSModule* GetModule( ISSModuleName moduleName );

	// 유저가 ISS 사용하는 스킬 판정 및 적용
	bool Occupy( int characterId, D3DXVECTOR3 direction );
	bool Destroy( int characterId, D3DXVECTOR3 direction );

	// 레이를 발사해서 레이안에 모듈이 있으면 module name을 반환
	ISSModuleName ModuleOnRay( const D3DXVECTOR3 &viewDirection, const D3DXVECTOR3 &startPoint );

	const CollisionBox* GetModuleCollisionBox( int idx ) { return m_ModuleList[idx].GetCollisionBox(); }
	
	std::tuple<TeamColor, float> GetModuleState( int moduleIdx );

private:
	std::array<ISSModule, MODULE_NUMBER> m_ModuleList;
	float	m_CurrentPos = 0.0f;
	float	m_Velocity = 0.0f;
};