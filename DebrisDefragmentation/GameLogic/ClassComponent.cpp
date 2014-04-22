#include "ClassComponent.h"
#include "Physics.h"
#include "Rigidbody.h"

ClassComponent::ClassComponent()
{
}


ClassComponent::~ClassComponent()
{
}



void ClassComponent::GoForward( D3DXVECTOR3 viewDirection, Rigidbody& rb )
{
	// 가속 시작 시점 기록 - 타임 스탬프로 문제 해결
	// 나중에는 타이머 만들어서 써볼까?
	m_AccelerationStartTime = timeGetTime();
	m_IsAccelerating = true;

	D3DXVECTOR3 normalVec( 0, 0, 0 );
	//D3DXVECTOR3 viewDirection( GetViewDirection() );
	Physics::GetNormalVector( &viewDirection, &normalVec );

	// 조심해!
	// 가속도 가중치 하드 코딩 수정 할 것, 	
	// 여기 normalvector가 아니고 view direction을 쓰고있음, 전체구조 손보면 확인할 것.
	rb.m_Acceleration += ( normalVec * ACCELERATION_WEIGHT );
}

void ClassComponent::Stop( Rigidbody& rb )
{
	// 장비를 정지합니다. 어 안되잖아? 어? 저, 정지가 안 돼, 정지시킬 수가 없어. 안-돼!
	rb.m_Acceleration = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	rb.m_Velocity = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
}

void ClassComponent::LookAt( float x, float y, float z, D3DXVECTOR3& rotation )
{
	// 조심해!
	// 회전 각도 가중치 하드 코딩 수정 할 것
	// SetRotation( x / 500, y / 500, 0 );
	//IncreaseRotationX( x / 10 );
	rotation += D3DXVECTOR3( x, y, z ) * MOUSE_ROTATION_WEIGHT;

// 	rotation.x += x / MOUSE_ROTATION_WEIGHT;
// 	rotation.x += y / MOUSE_ROTATION_WEIGHT;
// 	//IncreaseRotationY( y / 10 );

}