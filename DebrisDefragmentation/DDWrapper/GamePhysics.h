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
		// ���� ���۰� ���� ���� ó��.
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

		// ���� ������ �ƴ����� �˷��ش�.
		bool IsAccelation() { return m_IsAccelerating; }

		// �� ���� �ð��� ��ȯ�Ѵ�.
		DWORD TimeOfAccelation() { return m_dTime; }

	private:
		// ���� �ð��� ������Ʈ�Ѵ�.
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

		// ���
		void MoveObject( GameModel^ object, float velocityX, float velocityY, float velocityZ, float dt )
		{
			DDVECTOR3 result = object->GetPosition();
			DDVECTOR3 velocity = DDVECTOR3( velocityX, velocityY, velocityZ );
			CalcCurrentPosition( result, velocity, dt );

			object->SetPosition( result );
		}

		// ���
		// ���� : velocity ���� ���������� �����Ƿ� ȣ���� �ʿ��� �Ź� dt��ŭ �����ؾ� �Ѵ�.
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
				// ���� ��. false�� ������ ȣ���� �ʿ����� ���ӵ� ����� 0���� �����.
				return false;
			}
			else
			{
				// ���� OK
				return true;
			}
		}

		// �ڷ����� �޶� C#���� �ٷ� ������ ����
		// �� ���ĺ��ô�
	private:
		/*
		input : ���� ��ġ, �ӵ�, �ð� ��ȭ��
		output : ������Ʈ�� ���� ��ġ
		���� : ��ӿ�� ��� ���, ���ӵ��� ���� ����� �ʿ��ϸ� �����ε��� �Լ� ����� ��
		*/
		void CalcCurrentPosition( _Inout_ DDVECTOR3& pos, const DDVECTOR3& velocity, float dt )
		{
			Physics::CalcCurrentPosition( &pos, velocity, dt );
		}
		/*
		input : ���� ��ġ, ���� �ӵ�, ���ӵ�, �ð� ��ȭ��
		output : ������Ʈ�� ���� ��ġ, ������Ʈ�� ���� �ӵ�
		���� : ���ӵ��� ���� ��� ��� ���, ��ӿ�� ��� �����ε��� �Լ� ����� ��
		*/
		void CalcCurrentPosition( _Inout_ DDVECTOR3& pos, _Inout_ DDVECTOR3& velocity, const DDVECTOR3& acceleration, float dt )
		{
			Physics::CalcCurrentPosition( &pos, &velocity, acceleration, dt );
		}
		/*
		input : ���� ���Ϳ� ����� ����� ���� �ּ�
		output : ���� ������ ��� ����
		*/
		void GetNormalVector( _In_ DDVECTOR3* srcVec, _Out_ DDVECTOR3* normalVec )
		{
			Physics::GetNormalVector( srcVec, normalVec );
		}

		PhysicsData* m_pPhysicsData;
	};

}