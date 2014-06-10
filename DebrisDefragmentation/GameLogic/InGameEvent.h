#pragma once

#include "GameOption.h"

class InGameEvent
{
public:
	InGameEvent();
	virtual ~InGameEvent();

	// 다음 실행할 이벤트를 설정한다
	void Init();

	// 이벤트 실행 - 현재 설정된 이벤트가 무엇인지에 따라 적합한 함수 호출
	virtual void Run() = 0;

	// 남은 시간을 업데이트하고, 지금 이벤트를 실행할 지 결정
	bool Update( float dt );

	// 현재 이벤트까지 남은 시간을 알려준다.
	float GetRemainTime() { return m_Timer; }

	// 다음에 실행 될 이벤트 종류를 알려준다.
	GameEvent GetEventType() { return m_Event; }

protected:
	GameEvent	m_Event = GameEvent::NO_EVENT;
	float		m_Timer = 0.0f;

	// 이벤트가 플레이어에게 접근하는 방향 - 단위 벡터로 저장한다.
	D3DXVECTOR3 m_Direction;
};

