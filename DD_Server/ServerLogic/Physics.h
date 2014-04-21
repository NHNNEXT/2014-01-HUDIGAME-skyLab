#pragma once

#include "GameConfig.h"
#include "CollisionBox.h"

/*
�ۼ��� : �ְ��
�ۼ��� : 2014. 4. 6
���� : ������ ��� ����(��ü �, ȸ��, �浹 ��)

�ϴ� ���� �� ���� ����� ������ �����ؼ� ���ϴ� ��
*/

namespace Physics
{
	/*
	input : ���� ��ġ, �ӵ�, �ð� ��ȭ��
	output : ������Ʈ�� ���� ��ġ
	���� : ��ӿ�� ��� ���, ���ӵ��� ���� ����� �ʿ��ϸ� �����ε��� �Լ� ����� ��
	*/
	inline void CalcCurrentPosition( _Inout_ D3DXVECTOR3* pos, _In_ const D3DXVECTOR3 &velocity, _In_ float dt )
	{
		// s' = s + v * t	

		pos->x = pos->x + ( velocity.x * dt );
		pos->y = pos->y + ( velocity.y * dt );
		pos->z = pos->z + ( velocity.z * dt );
	}

	/*
	input : ���� ��ġ, ���� �ӵ�, ���ӵ�, �ð� ��ȭ��
	output : ������Ʈ�� ���� ��ġ, ������Ʈ�� ���� �ӵ�
	���� : ���ӵ��� ���� ��� ��� ���, ��ӿ�� ��� �����ε��� �Լ� ����� ��
	*/
	inline void CalcCurrentPosition( _Inout_ D3DXVECTOR3* pos, _Inout_ D3DXVECTOR3* velocity, _In_ const D3DXVECTOR3 &acceleration, _In_ float dt )
	{
		// s' = s + v * t + 1/2 * a * t^2

		// v * t
		CalcCurrentPosition( pos, *velocity, dt );

		// v' = v + a * t
		CalcCurrentPosition( velocity, acceleration, dt );

		// 1/2 * a * t^2

		pos->x = pos->x + ( 0.5f * acceleration.x * dt * dt );
		pos->y = pos->y + ( 0.5f * acceleration.y * dt * dt );
		pos->z = pos->z + ( 0.5f * acceleration.z * dt * dt );
	}

	/*
	input : ���� ���Ϳ� ����� ����� ���� �ּ�
	output : ���� ������ ��� ����
	*/
	inline void GetNormalVector( _In_ D3DXVECTOR3* srcVec, _Out_ D3DXVECTOR3* normalVec )
	{
		float length = sqrtf( srcVec->x * srcVec->x + srcVec->y * srcVec->y + srcVec->z * srcVec->z );

		normalVec->x = srcVec->x / length;
		normalVec->y = srcVec->y / length;
		normalVec->z = srcVec->z / length;
	}

	void static SATtest( const D3DXVECTOR3& axis, const D3DXVECTOR3& centerPos, float& axisLen, float& minAlong, float& maxAlong )
	{
		minAlong = HUGE, maxAlong = -HUGE;

		float dotVal = dotVal = D3DXVec3Dot( &axis, &centerPos );
		minAlong = dotVal - axisLen;
		maxAlong = dotVal + axisLen;
	}

	void static SATtest( const D3DXVECTOR3& axis, const std::array<D3DXVECTOR3, 8>& points, float& minAlong, float& maxAlong )
	{
		minAlong = HUGE, maxAlong = -HUGE;

		for ( int i = 0; i < 8; i++ )
		{
			// �־��� �� ����Ʈ���� axis�� �����ؼ� �ִ� �ּ� ���� �ٲ��ش�.
			float dotVal = D3DXVec3Dot( &axis, &points[i] );
			if ( dotVal < minAlong )  minAlong = dotVal;
			if ( dotVal > maxAlong )  maxAlong = dotVal;
		}
	}

	// val���� lowerBound�� upperBound ������ ������ ����
	inline bool isBetweenOrdered( float val, float lowerBound, float upperBound ) {
		return lowerBound <= val && val <= upperBound;
	}

	// �� �ִ� �ּ� ������ ���� ��ġ���� ����
	bool static overlaps( float min1, float max1, float min2, float max2 )
	{
		return isBetweenOrdered( min2, min1, max1 ) || isBetweenOrdered( min1, min2, max2 );
	}

	inline void transformOBB( ST_OBB &box )
	{
		D3DXVECTOR4 tempMat;

		// ���� ��ġ
		D3DXVec3Transform( &tempMat, &box.m_CenterPos, box.m_Transform );
		box.m_CenterPos = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

		// �� �� ��ǥ
		D3DXVec3Transform( &tempMat, &box.m_PointList[0], box.m_Transform );
		box.m_PointList[0] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

		D3DXVec3Transform( &tempMat, &box.m_PointList[1], box.m_Transform );
		box.m_PointList[1] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

		D3DXVec3Transform( &tempMat, &box.m_PointList[2], box.m_Transform );
		box.m_PointList[2] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

		D3DXVec3Transform( &tempMat, &box.m_PointList[3], box.m_Transform );
		box.m_PointList[3] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

		D3DXVec3Transform( &tempMat, &box.m_PointList[4], box.m_Transform );
		box.m_PointList[4] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

		D3DXVec3Transform( &tempMat, &box.m_PointList[5], box.m_Transform );
		box.m_PointList[5] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

		D3DXVec3Transform( &tempMat, &box.m_PointList[6], box.m_Transform );
		box.m_PointList[6] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

		D3DXVec3Transform( &tempMat, &box.m_PointList[7], box.m_Transform );
		box.m_PointList[7] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

		// ��
		for ( int i = 0; i < 3; ++i )
		{
			// ������ ���� 0���� �ؾ� �����̵� ���� ���Ϳ� �ݿ����� ����
			D3DXVECTOR4 tempAxis = D3DXVECTOR4( box.m_AxisDir[i].x, box.m_AxisDir[i].y, box.m_AxisDir[i].z, 0 );

			D3DXVec4Transform( &tempMat, &tempAxis, box.m_Transform );
			box.m_AxisDir[i] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );
		}
	}

	bool static IsCollide( ST_OBB box1, ST_OBB box2 )
	{
		transformOBB( box1 );
		transformOBB( box2 );

		for ( int i = 0; i < 3; i++ )
		{
			// ù ��° �ڽ��� �࿡ ���ؼ� �浹 Ȯ��
			float box1Min, box1Max, box2Min, box2Max;
			SATtest( box1.m_AxisDir[i], box1.m_CenterPos, box1.m_AxisLen[i], box1Min, box1Max );
			SATtest( box1.m_AxisDir[i], box2.m_PointList, box2Min, box2Max );
			if ( !overlaps( box1Min, box1Max, box2Min, box2Max ) )
			{
				return false;
			}

			// �� ��° �ڽ��� �࿡ ���ؼ� �浹 Ȯ��
			SATtest( box2.m_AxisDir[i], box1.m_PointList, box1Min, box1Max );
			SATtest( box2.m_AxisDir[i], box2.m_CenterPos, box2.m_AxisLen[i], box2Min, box2Max );
			if ( !overlaps( box1Min, box1Max, box2Min, box2Max ) )
			{
				return false;
			}

			/*
			for ( int j = 0; j < 3; ++j )
			{
			D3DXVECTOR3 tempAxis;
			D3DXVec3Cross( &tempAxis, &box1.m_AxisDir[i], &box2.m_AxisDir[j] );

			SATtest( tempAxis, box1.m_PointList, box1Min, box1Max );
			SATtest( tempAxis, box2.m_PointList, box1Min, box1Max );
			if ( !overlaps( box1Min, box1Max, box2Min, box2Max ) )
			{
			return false;
			}
			}
			*/
		}

		// ��� �࿡ ���ؼ� ��ħ�� �߻��ϸ� �浹�� ����
		return true;
	}
};

