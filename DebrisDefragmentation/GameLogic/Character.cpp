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
}

void Character::UpdateItSelf( float dTime )
{
	// 변환 행렬 업데이트 - 충돌 박스가 연산할 때 이 행렬값이 최신으로 갱신되어 있어야 하므로
	D3DXQUATERNION	qRotation;
	D3DXQuaternionRotationYawPitchRoll( &qRotation, D3DXToRadian( GetTransform()->GetRotationY() ), D3DXToRadian( GetTransform()->GetRotationX() ), D3DXToRadian( GetTransform()->GetRotationZ() ) );
	D3DXMatrixTransformation( &m_Matrix, NULL, NULL, &GetTransform()->GetScale(), NULL, &qRotation, &GetTransform()->GetPosition() );

	if ( m_CharacterClass->IsSpinning() )
	{
		m_CharacterClass->AddSpinTime( dTime );

		// 회전축을 기준으로 물체를 회전시킵니다.
		D3DXMATRIXA16 spinTransform;
		D3DXVECTOR3 tmpSpinAxis = GetClassComponent()->GetSpinAxis();
		float tmpSpinAngle = GetClassComponent()->GetSpinAngle();
		D3DXMatrixRotationAxis( &spinTransform, &tmpSpinAxis, tmpSpinAngle * m_CharacterClass->GetSpinTime() );
		D3DXMatrixMultiply( &m_Matrix, &m_Matrix, &spinTransform );
	}

	if ( m_CharacterClass->IsAccelerating() )
	{
		if ( timeGetTime( ) - m_CharacterClass->GetAccelerationStartTime() > ACCELERATION_TIME )
		{
			// 가속 끝났다
			m_CharacterClass->SetIsAccelerating( false );			
			m_CharacterClass->SetAcceleration( ZERO_VECTOR3 );
		}
	}

	D3DXVECTOR3 tmpVec3 = GetTransform()->GetPosition();
	D3DXVECTOR3 tmpVel = GetClassComponent()->GetVelocity();
	Physics::CalcCurrentPosition( &tmpVec3, &tmpVel, GetClassComponent()->GetAcceleration(), dTime );
	GetTransform()->SetPosition( tmpVec3 );
	GetClassComponent()->SetVelocity( tmpVel );

	// 산소량 감소등의 작업 처리
	GetClassComponent()->Update( dTime );

	// printf_s( "%f / %f / %f\n", m_Position.x, m_Position.y, m_Position.z );
}

void Character::ChangeClass( CharacterClass newClass )
{
	switch ( newClass )
	{
	case CharacterClass::NO_CLASS:
		// break;
	case CharacterClass::STRIKER:
		// break;
	case CharacterClass::ENGINEER:
		// break;
	case CharacterClass::PROTECTOR:
		// break;
	default:
		// 여기 들어오지 마라
		assert( false );
		break;
	}
}

