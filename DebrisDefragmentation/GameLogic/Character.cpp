#include "stdafx.h"
#include "Character.h"

#include "Physics.h"

Character::~Character()
{
}

void Character::Init()
{
	// collision box는 어떤 객체이냐에 따라서 다르게 구현된다.
	m_CollisionBox.m_CenterPos = D3DXVECTOR3( CHARACTER_CB_CENTER_POS_X, CHARACTER_CB_CENTER_POS_Y, CHARACTER_CB_CENTER_POS_Z );

	m_CollisionBox.m_AxisLen[0] = CHARACTER_CB_LENGTH_X;
	m_CollisionBox.m_AxisLen[1] = CHARACTER_CB_LENGTH_Y;
	m_CollisionBox.m_AxisLen[2] = CHARACTER_CB_LENGTH_Z;

	// 각각 X, Y, Z 축
	m_CollisionBox.m_AxisDir[0] = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
	m_CollisionBox.m_AxisDir[1] = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	m_CollisionBox.m_AxisDir[2] = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );

	m_CollisionBox.m_PointList[0] = D3DXVECTOR3(
		CHARACTER_CB_CENTER_POS_X - CHARACTER_CB_LENGTH_X,
		CHARACTER_CB_CENTER_POS_Y + CHARACTER_CB_LENGTH_Y,
		CHARACTER_CB_CENTER_POS_Z + CHARACTER_CB_LENGTH_Z
		);
	m_CollisionBox.m_PointList[1] = D3DXVECTOR3(
		CHARACTER_CB_CENTER_POS_X + CHARACTER_CB_LENGTH_X,
		CHARACTER_CB_CENTER_POS_Y + CHARACTER_CB_LENGTH_Y,
		CHARACTER_CB_CENTER_POS_Z + CHARACTER_CB_LENGTH_Z
		);
	m_CollisionBox.m_PointList[2] = D3DXVECTOR3(
		CHARACTER_CB_CENTER_POS_X + CHARACTER_CB_LENGTH_X,
		CHARACTER_CB_CENTER_POS_Y + CHARACTER_CB_LENGTH_Y,
		CHARACTER_CB_CENTER_POS_Z - CHARACTER_CB_LENGTH_Z
		);
	m_CollisionBox.m_PointList[3] = D3DXVECTOR3(
		CHARACTER_CB_CENTER_POS_X - CHARACTER_CB_LENGTH_X,
		CHARACTER_CB_CENTER_POS_Y + CHARACTER_CB_LENGTH_Y,
		CHARACTER_CB_CENTER_POS_Z - CHARACTER_CB_LENGTH_Z
		);
	m_CollisionBox.m_PointList[4] = D3DXVECTOR3(
		CHARACTER_CB_CENTER_POS_X - CHARACTER_CB_LENGTH_X,
		CHARACTER_CB_CENTER_POS_Y - CHARACTER_CB_LENGTH_Y,
		CHARACTER_CB_CENTER_POS_Z + CHARACTER_CB_LENGTH_Z
		);
	m_CollisionBox.m_PointList[5] = D3DXVECTOR3(
		CHARACTER_CB_CENTER_POS_X + CHARACTER_CB_LENGTH_X,
		CHARACTER_CB_CENTER_POS_Y - CHARACTER_CB_LENGTH_Y,
		CHARACTER_CB_CENTER_POS_Z + CHARACTER_CB_LENGTH_Z
		);
	m_CollisionBox.m_PointList[6] = D3DXVECTOR3(
		CHARACTER_CB_CENTER_POS_X + CHARACTER_CB_LENGTH_X,
		CHARACTER_CB_CENTER_POS_Y - CHARACTER_CB_LENGTH_Y,
		CHARACTER_CB_CENTER_POS_Z - CHARACTER_CB_LENGTH_Z
		);
	m_CollisionBox.m_PointList[7] = D3DXVECTOR3(
		CHARACTER_CB_CENTER_POS_X - CHARACTER_CB_LENGTH_X,
		CHARACTER_CB_CENTER_POS_Y - CHARACTER_CB_LENGTH_Y,
		CHARACTER_CB_CENTER_POS_Z - CHARACTER_CB_LENGTH_Z
		);

	m_CollisionBox.m_Radius = sqrt( CHARACTER_CB_LENGTH_X * CHARACTER_CB_LENGTH_X 
									+ CHARACTER_CB_LENGTH_Y * CHARACTER_CB_LENGTH_Y 
									+ CHARACTER_CB_LENGTH_Z * CHARACTER_CB_LENGTH_Z );

	InitTeamPosition();
	SetVelocity( ZERO_VECTOR3 );

	m_SpeedConstant = 1.0f;
	m_SpinTime = 0;
	m_AccelerationStartTime = 0;
	m_Rigidbody.Init();
	m_CharacterClass->ResetStatus();
}

void Character::InitTeamPosition()
{
	switch ( GetClassComponent()->GetTeam() )
	{
	case TeamColor::RED:
		GetTransform()->SetPosition( RED_TEAM_POSITION );
		GetTransform()->SetRotation( RED_TEAM_ROTATION );
		break;
	case TeamColor::BLUE:
		GetTransform()->SetPosition( BLUE_TEAM_POSITION );
		GetTransform()->SetRotation( BLUE_TEAM_ROTATION );
		break;
	default:
		break;
	}
}

void Character::UpdateItSelf( float dTime )
{
	// 가속
	if ( IsAccelerating() )
	{
		if ( timeGetTime() - GetAccelerationStartTime() > ACCELERATION_TIME )
		{
			// 가속 끝났다
			SetIsAccelerating( false );
			SetAcceleration( ZERO_VECTOR3 );
		}
	}

	if ( !m_CharacterClass->IsAlive() )
	{
		printf_s( "player %d is dead \n", m_CharacterId );
		return;
	}

	m_Matrix = GetTransform()->MatrixTransform();

	if ( IsSpinning() )
	{
		AddSpinTime( dTime );

		// 회전축을 기준으로 물체를 회전시킵니다.
		D3DXMATRIXA16 spinTransform;
		D3DXVECTOR3 tmpSpinAxis = GetSpinAxis();
		float tmpSpinAngle = GetSpinAngle();
		D3DXMatrixRotationAxis( &spinTransform, &tmpSpinAxis, tmpSpinAngle * GetSpinTime() );
		// D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &spinTransform );
		D3DXMatrixMultiply( &m_Matrix, &spinTransform, &m_Matrix );
	}

	D3DXVECTOR3 tmpVec3 = GetTransform()->GetPosition();
	D3DXVECTOR3 tmpVel = GetVelocity();
	Physics::CalcCurrentPosition( &tmpVec3, &tmpVel, GetAcceleration(), dTime );
	GetTransform()->SetPosition( tmpVec3 );
	SetVelocity( tmpVel );

	// 산소량 감소등의 작업 처리
	GetClassComponent()->Update( dTime );
}

void Character::ChangeClass( CharacterClass newClass )
{
	// 변신!
	m_CharacterClass = ClassComponent::Create( newClass );

	// 조심해!!
	// 위치 초기화 할까?
}

