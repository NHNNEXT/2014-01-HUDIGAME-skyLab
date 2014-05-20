/*
	게임 내부에서 인터랙션이 발생하는 모든 것들의 최상위 클래스
	위치와 크기, 회전 등의 정보를 가지고 있다. (DDFramework의 Object와 비슷) 
	움직임은 하위 클래스에서 구현할 것

*/

#pragma once

#include "GameOption.h"
#include "CollisionBox.h"
#include "Transform.h"

class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();

	virtual void Update( float dTime );

	// 현재 바라보는 방향의 벡터를 월드좌표계 기준으로 반환
	D3DXVECTOR3 GetViewDirection();

	Transform* GetTransform() { return &m_Transform; }

	// 인자로 넣은 회전 변환을 적용한 상태에서 바라보는 방향을 월드 좌표계 기준으로 반환
	D3DXVECTOR3 GetViewDirection( float x, float y, float z );
	D3DXVECTOR3 GetViewDirection( const D3DXVECTOR3& direction );

	// 현재 변환 행렬이 적용된 충돌 박스 리턴
	const CollisionBox* GetCollisionBox();

protected:
	D3DXMATRIXA16	m_Matrix;
	Transform		m_Transform;
	CollisionBox	m_CollisionBox;		// 충돌 박스의 기본 값 저장
	CollisionBox	m_TransformedBox;	// 물체가 회전함에 따라 기본 박스가 변형된 값 저장 
	///# 계산할 때마다 스택에 생성하느냐? vs 힙에 생성해놓고 쓰느냐?의 차이.. 의도대로 캐시 용도라면 멤버 변수 이름에 Cache네이밍을 붙여주는게 좋다.
	
	// 로컬 좌표계 상의 충돌 박스 정보는 m_CollisionBox에 저장되어 있고
	// 충돌 체크할 때 현재의 m_Matrix에 저장된 변환을 적용한 박스가 필요
	// 결국 m_CollisionBox에 m_Matrix를 곱한 결과를 리턴해줘야 하는데 
	// 매번 체크할 때마다 복사 생성하는 비용을 줄이기 위해 내부에 그 결과를 저장하고 외부에서 그걸 참조
	// 변환 결과를 m_CollisionBox에 저장하면 다음 변환 때 월드 좌표계 기준의 충돌박스를 다시 월드 좌표계로 변환하게 되므로 분리해서 저장

private:
	virtual void UpdateItSelf( float dTime ) { UNREFERENCED_PARAMETER( dTime ); }
};

