#pragma once

#include "DDObject.h"
#include "DDPoint.h"
#include "DDInputSystem.h"

class DDScene :
	public DDObject
{
public:
	DDScene();
	virtual ~DDScene();

	static DDScene* Create();

	virtual void Render();
	virtual void Update( float dTime );

	// 작성자 : 최경욱 4.8
	// input : int값의 키
	// output : 인자로 넘긴 키의 현재 상태를 받아오는 함수
	KeyState GetKeyState( int key );

	// input : 없음
	// output : 현재 마우스 좌표 받아오는 함수
	DDPoint GetMousePosition();

protected:
	DDPoint m_PrevMousePosition;
	// 여기서 나중에 skybox 만들면 될 거 같음(4.6 성환)
	//LPD3DXSPRITE	m_pSprite;
};

