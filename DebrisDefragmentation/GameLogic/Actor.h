/*
	Actor를 상속받은 캐릭터
	움직임과 각종 스킬들의 인터페이스를 구현한다.
	세부 클래스는 하위 클래스에서 구현할 것
*/

#pragma once

#include "BaseObject.h"
#include "rigidbody.h"
#include "ClassComponent.h"

class Actor : public BaseObject
{
public:
	Actor( CharacterClass actorClass = CharacterClass::STRIKER );
	virtual ~Actor();

	void	InitTeamPosition();
	ClassComponent* GetClassComponent() { return m_CharacterClass.get(); }

	void	GoForward();
	void	Stop();
	void	TurnBody( float x, float y, float z );

	void		SetTeam( TeamColor color ) { m_CharacterClass->SetTeam( color ); }
	TeamColor	GetTeam() { return m_CharacterClass->GetTeam(); }

	D3DXVECTOR3 GetVelocity() const { return m_CharacterClass->GetVelocity(); }
	void	IncreaseVelocity( const D3DXVECTOR3 &deltaVelocity );

	//float	GetMass() const { return m_RigidBody.m_Mass; }
	bool	IsMoving() const { return m_MovingFlag; }
	void	SetMovingFlag( bool flag ) { m_MovingFlag = flag; }

protected:
	std::shared_ptr<ClassComponent> m_CharacterClass;
	//Rigidbody	m_RigidBody;	
	bool		m_MovingFlag = true;

private:
	virtual void UpdateItSelf( float dTime ) { UNREFERENCED_PARAMETER( dTime ); }
};

