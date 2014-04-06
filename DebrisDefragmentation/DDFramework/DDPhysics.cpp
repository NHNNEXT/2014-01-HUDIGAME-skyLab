#include "stdafx.h"
#include "DDPhysics.h"


DDPhysics::DDPhysics()
{
}

DDPhysics::~DDPhysics()
{
}

void DDPhysics::CalcCurrentPosition( _Inout_ DDVector3* pos, _In_ const DDVector3 &velocity, _In_ float dt )
{
	// s' = s + v * t
	pos->SetVector(
		pos->GetX() + ( velocity.GetX() * dt ),
		pos->GetY() + ( velocity.GetY() * dt ),
		pos->GetZ() + ( velocity.GetZ() * dt )
		);
}

void DDPhysics::CalcCurrentPosition( _Inout_ DDVector3* pos, _Inout_ DDVector3* velocity, _In_ const DDVector3 &acceleration, _In_ float dt )
{
	// s' = s + v * t + 1/2 * a * t^2

	// v * t
	CalcCurrentPosition( pos, *velocity, dt );

	// v' = v + a * t
	CalcCurrentPosition( velocity, acceleration, dt );

	// 1/2 * a * t^2
	pos->SetVector(
		pos->GetX() + ( 0.5f * acceleration.GetX() * dt * dt ),
		pos->GetY() + ( 0.5f * acceleration.GetY() * dt * dt ),
		pos->GetZ() + ( 0.5f * acceleration.GetZ() * dt * dt )
		);
}