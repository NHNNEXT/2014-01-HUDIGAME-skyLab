#pragma once
#include <vcclr.h>

#include "GameModel.h"
#include "..\GameLogic\Physics.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DDWrapper
{
	public class PhysicsData
	{
	public:
		// 가속 시작과 끝에 대한 처리.
		void StartAccelation()
		{
			if ( m_IsAccelerating )
			{
				Update();
			}
			else
			{
				m_StartTime = timeGetTime();
				m_IsAccelerating = true;
			}
		}

		void StopAccelation()
		{
			m_StartTime = 0;
			m_dTime = 0;
			m_IsAccelerating = false;
		}

		// 가속 중인지 아닌지를 알려준다.
		bool IsAccelation() { return m_IsAccelerating; }

		// 총 가속 시간을 반환한다.
		DWORD TimeOfAccelation() { return m_dTime; }

	private:
		// 가속 시간을 업데이트한다.
		void Update() { m_dTime = timeGetTime() - m_StartTime; }

		DWORD m_dTime = DWORD(0.0);
		DWORD m_StartTime = DWORD(0.0);

		bool m_IsAccelerating = false;
	};

	public ref class GamePhysics
	{
	public:
		GamePhysics() : m_pPhysicsData( new PhysicsData() ) {};
		~GamePhysics() {};

		// 등속
		void MoveObject( GameModel^ object, float velocityX, float velocityY, float velocityZ, float dt )
		{
			DDVECTOR3 result = object->GetPosition();
			DDVECTOR3 velocity = DDVECTOR3( velocityX, velocityY, velocityZ );
			CalcCurrentPosition( result, velocity, dt );

			object->SetPosition( result );
		}

		// 등가속
		// 주의 : velocity 값을 변경해주지 않으므로 호출한 쪽에서 매번 dt만큼 갱신해야 한다.
		bool AccelObject( GameModel^ object, float velocityX, float velocityY, float velocityZ,
			float accelX, float accelY, float accelZ, float dt )
		{
			m_pPhysicsData->StartAccelation();

			DDVECTOR3 result = object->GetPosition();
			DDVECTOR3 velocity = DDVECTOR3( velocityX, velocityY, velocityZ );
			DDVECTOR3 accel = DDVECTOR3( accelX, accelY, accelZ );
			CalcCurrentPosition( result, velocity, accel, dt );

			object->SetPosition( result );

			if ( m_pPhysicsData->TimeOfAccelation() > 500 )
			{
				m_pPhysicsData->StopAccelation();
				// 가속 끝. false를 받으면 호출한 쪽에서는 가속도 행렬을 0으로 만든다.
				return false;
			}
			else
			{
				// 가속 OK
				return true;
			}
		}

		// 자료형이 달라서 C#에서 바로 쓰지는 못함
		// 잘 고쳐봅시다
	private:
		/*
		input : 현재 위치, 속도, 시간 변화량
		output : 업데이트된 현재 위치
		주의 : 등속운동인 경우 사용, 가속도에 의한 계산이 필요하면 오버로딩된 함수 사용할 것
		*/
		void CalcCurrentPosition( _Inout_ DDVECTOR3& pos, const DDVECTOR3& velocity, float dt )
		{
			Physics::CalcCurrentPosition( &pos, velocity, dt );
		}
		/*
		input : 현재 위치, 현재 속도, 가속도, 시간 변화량
		output : 업데이트된 현재 위치, 업데이트된 현재 속도
		주의 : 가속도에 의한 운동인 경우 사용, 등속운동의 경우 오버로딩된 함수 사용할 것
		*/
		void CalcCurrentPosition( _Inout_ DDVECTOR3& pos, _Inout_ DDVECTOR3& velocity, const DDVECTOR3& acceleration, float dt )
		{
			Physics::CalcCurrentPosition( &pos, &velocity, acceleration, dt );
		}
		/*
		input : 원본 벡터와 결과가 저장될 벡터 주소
		output : 원본 벡터의 노멀 벡터
		*/
		void GetNormalVector( _In_ DDVECTOR3* srcVec, _Out_ DDVECTOR3* normalVec )
		{
			Physics::GetNormalVector( srcVec, normalVec );
		}

		PhysicsData* m_pPhysicsData;
	};

}