#include "Avatar.h"
#include "Physics.h"
#include "Rigidbody.h"

Avatar::Avatar()
{
}


Avatar::~Avatar()
{
}



void Avatar::_GoForward( D3DXVECTOR3 viewDirection, RIGIDBODY& rigidbody )
{
	// 가속 시작 시점 기록 - 타임 스탬프로 문제 해결
	// 나중에는 타이머 만들어서 써볼까?
	m_AccelerationStartTime = timeGetTime();
	m_IsAccelerating = true;

	D3DXVECTOR3 normalVec( 0, 0, 0 );
	//D3DXVECTOR3 viewDirection( GetViewDirection() );

	// agebreak : 아래 함수 안에 가보면.. 노말벡터를 구하는게 아님. Normalize 즉 정규화 하는거임. 
	// D3DXVec3Normalize() 함수를 사용하면 됨. 
	Physics::GetNormalVector( &viewDirection, &normalVec );
	
	// 조심해!
	// 가속도 가중치 하드 코딩 수정 할 것, 	
	// 여기 normalvector가 아니고 view direction을 쓰고있음, 전체구조 손보면 확인할 것.
	rigidbody.acceleration += ( normalVec * ACCELERATION_WEIGHT );
}

void Avatar::_Stop( RIGIDBODY& rigidbody )
{
	// 장비를 정지합니다. 어 안되잖아? 어? 저, 정지가 안 돼, 정지시킬 수가 없어. 안-돼!
	rigidbody.acceleration = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	rigidbody.velocity = D3DXVECTOR3( 0.0f, 0.0f, 0.0f ); // agebreak : 제로 벡터를 디파인 해두면 이런 경우에 편함	
	
}

// agebreak : 무슨 함수인지 명확하지 않음. 걍 벡터에 더하는것 같은데.. 함수 이름하고 매치가 안됨. 그리고 inout을 쓰지말고 리턴을 활용하는것이 깔끔함
// 그리고 MS의 규약에 따라서 output 인자는 맨 앞에 둘것!!
void Avatar::_RotateDirection( float x, float y, D3DXVECTOR3& rotation )
{
	// 조심해!
	// 회전 각도 가중치 하드 코딩 수정 할 것
	// SetRotation( x / 500, y / 500, 0 );
	//IncreaseRotationX( x / 10 );
	float z = 0;
	rotation += D3DXVECTOR3( x, y, z ) / MOUSE_ROTATION_WEIGHT;

// 	rotation.x += x / MOUSE_ROTATION_WEIGHT;
// 	rotation.x += y / MOUSE_ROTATION_WEIGHT;
// 	//IncreaseRotationY( y / 10 );

}