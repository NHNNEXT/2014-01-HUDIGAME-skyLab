﻿#pragma once

#include "GameConfig.h"
#include "CollisionBox.h"
#include <vector>
/*
작성자 : 최경욱
작성일 : 2014. 4. 6
내용 : 물리적 계산 수행(물체 운동, 회전, 충돌 등)

일단 다음 주 로직 만들기 전에는 복사해서 씁니다 ㅠ
*/

namespace Physics
{
	/*
	input : 현재 위치, 속도, 시간 변화량
	output : 업데이트된 현재 위치
	주의 : 등속운동인 경우 사용, 가속도에 의한 계산이 필요하면 오버로딩된 함수 사용할 것
	*/
	inline void CalcCurrentPosition( _Inout_ D3DXVECTOR3* pos, _In_ const D3DXVECTOR3 &velocity, _In_ float dt )
	{
		// s' = s + v * t	

		pos->x = pos->x + ( velocity.x * dt );
		pos->y = pos->y + ( velocity.y * dt );
		pos->z = pos->z + ( velocity.z * dt );
	}

	/*
	input : 현재 위치, 현재 속도, 가속도, 시간 변화량
	output : 업데이트된 현재 위치, 업데이트된 현재 속도
	주의 : 가속도에 의한 운동인 경우 사용, 등속운동의 경우 오버로딩된 함수 사용할 것
	*/
	inline void CalcCurrentPosition( _Inout_ D3DXVECTOR3* pos, _Inout_ D3DXVECTOR3* velocity, _In_ const D3DXVECTOR3 &acceleration, _In_ float dt )
	{
		// s' = s + v * t + 1/2 * a * t^2

		// v' = v + a * t
		CalcCurrentPosition( velocity, acceleration, dt );

		// v * t
		CalcCurrentPosition( pos, *velocity, dt );

		// 1/2 * a * t^2
		pos->x = pos->x + ( 0.5f * acceleration.x * dt * dt );
		pos->y = pos->y + ( 0.5f * acceleration.y * dt * dt );
		pos->z = pos->z + ( 0.5f * acceleration.z * dt * dt );
	}

	/*
	input : 원본 벡터와 결과가 저장될 벡터 주소
	output : 원본 벡터의 노멀 벡터
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
		minAlong = static_cast<float>( HUGE );
		maxAlong = static_cast<float>( -HUGE );

		float dotVal = dotVal = D3DXVec3Dot( &axis, &centerPos );
		minAlong = dotVal - axisLen;
		maxAlong = dotVal + axisLen;
	}

	void static SATtest( const D3DXVECTOR3& axis, const std::array<D3DXVECTOR3, 8>& points, float& minAlong, float& maxAlong )
	{
		minAlong = static_cast<float>( HUGE );
		maxAlong = static_cast<float>( -HUGE );

		for ( int i = 0; i < 8; i++ )
		{
			// 주어진 점 리스트들을 axis에 투영해서 최대 최소 값을 바꿔준다.
			float dotVal = D3DXVec3Dot( &axis, &points[i] );
			if ( dotVal < minAlong )  minAlong = dotVal;
			if ( dotVal > maxAlong )  maxAlong = dotVal;
		}
	}

	// val값이 lowerBound와 upperBound 사이의 값인지 리턴
	inline bool IsBetweenOrdered( float val, float lowerBound, float upperBound ) {
		return lowerBound <= val && val <= upperBound;
	}

	// 두 최대 최소 구간이 서로 겹치는지 리턴
	bool static Overlaps( float min1, float max1, float min2, float max2 )
	{
		return IsBetweenOrdered( min2, min1, max1 ) || IsBetweenOrdered( min1, min2, max2 );
	}

	inline void TransformCollisionBox( CollisionBox &box )
	{
		D3DXVECTOR4 tempMat;

		// 현재 위치
		D3DXVec3Transform( &tempMat, &box.m_CenterPos, box.m_Transform );
		box.m_CenterPos = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );

		// 각 점 좌표
		D3DXVec3TransformCoordArray( 
			box.m_PointList.data(), sizeof( D3DXVECTOR3 ), 
			box.m_PointList.data(), sizeof( D3DXVECTOR3 ), 
			box.m_Transform, BOX_POINT_COUNT 
			);
		
		// 축
		for ( int i = 0; i < 3; ++i )
		{
			// 마지막 항을 0으로 해야 평행이동 값이 벡터에 반영되지 않음
			D3DXVECTOR4 tempAxis = D3DXVECTOR4( box.m_AxisDir[i].x, box.m_AxisDir[i].y, box.m_AxisDir[i].z, 0 );

			D3DXVec4Transform( &tempMat, &tempAxis, box.m_Transform );
			box.m_AxisDir[i] = D3DXVECTOR3( tempMat.x, tempMat.y, tempMat.z );
		}
	}

	bool static IsCollide( CollisionBox &box1, CollisionBox &box2 )
	{
		TransformCollisionBox( box1 );
		TransformCollisionBox( box2 );

		for ( int i = 0; i < 3; i++ )
		{
			// 첫 번째 박스의 축에 대해서 충돌 확인
			float box1Min, box1Max, box2Min, box2Max;
			SATtest( box1.m_AxisDir[i], box1.m_CenterPos, box1.m_AxisLen[i], box1Min, box1Max );
			SATtest( box1.m_AxisDir[i], box2.m_PointList, box2Min, box2Max );
			if ( !Overlaps( box1Min, box1Max, box2Min, box2Max ) )
			{
				return false;
			}

			// 두 번째 박스의 축에 대해서 충돌 확인
			SATtest( box2.m_AxisDir[i], box1.m_PointList, box1Min, box1Max );
			SATtest( box2.m_AxisDir[i], box2.m_CenterPos, box2.m_AxisLen[i], box2Min, box2Max );
			if ( !Overlaps( box1Min, box1Max, box2Min, box2Max ) )
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

		// 모든 축에 대해서 겹침이 발생하면 충돌로 판정
		return true;
	}

	bool static IntersectionCheck( const D3DXVECTOR3 &viewDirection, const D3DXVECTOR3 &startPoint, const CollisionBox &box )
	{
		float maxDistance = static_cast<float>( HUGE );
		float minDistance = static_cast<float>( -HUGE );

		for ( int i = 0; i < VECTOR_DIRECTION_3; ++i )
		{
			float dotVal = D3DXVec3Dot( &viewDirection, &box.m_AxisDir[i] );
			if ( dotVal == 0.0f )
			{
				// viewDirection의 출발점을 내적한 값이
				float rayStart = D3DXVec3Dot( &startPoint, &box.m_AxisDir[i] );
				float lowerBound = D3DXVec3Dot( &box.m_PointList[7], &box.m_AxisDir[i] ); // 바로 인덱스로 받아서 써도 될 것 같긴한데
				float upperBound = D3DXVec3Dot( &box.m_PointList[1], &box.m_AxisDir[i] );
				
				// box의 두 점을 내적한 값 사이에 있는지 확인
				if ( !IsBetweenOrdered( rayStart, lowerBound, upperBound ) )
				{
					return false;
				}
			}
			else
			{
				// box.m_AxisDir[i]에 수직인 두 plane을 추출해서 
				// viewDirection과 두 평면의 교차점을 찾는다
				D3DXPLANE lowerPlane, upperPlane;
				D3DXPlaneFromPointNormal( &lowerPlane, &box.m_PointList[7], &box.m_AxisDir[i] );
				D3DXPlaneFromPointNormal( &upperPlane, &box.m_PointList[1], &box.m_AxisDir[i] );

				D3DXVECTOR3 lowerPoint, upperPoint;
				D3DXVECTOR3 endPoint = startPoint + viewDirection * SKILL_RANGE;
				D3DXPlaneIntersectLine( &lowerPoint, &lowerPlane, &startPoint, &endPoint );
				D3DXPlaneIntersectLine( &upperPoint, &upperPlane, &startPoint, &endPoint );

				if ( lowerPoint == NULL || upperPoint == NULL )
					return false;
				
				// 두 점과 viewDrection과의 거리를 구해서
				float tempDistance1, tempDistance2, tempMax, tempMin;
				tempDistance1 = tempDistance2 = tempMax = tempMin = 0.0f;
				
				tempDistance1 = D3DXVec3Length( &( lowerPoint - startPoint ) );
				tempDistance2 = D3DXVec3Length( &( upperPoint - startPoint ) );

				if ( tempDistance1 > tempDistance2 )
				{
					tempMax = tempDistance1;
					tempMin = tempDistance2;
				}
				else
				{
					tempMax = tempDistance2;
					tempMin = tempDistance1;
				}

				// 각 축에 대해 수직인 면과 viewDirection이 만나는 점들의 거리에 따른 in out은 
				// 다른 축에 대한 점들의 in out 조합 중, 가장 좁은 영역의 안에 있거나 모두 밖에 있어야 한다.
				if ( ( tempMax > maxDistance && tempMin < minDistance )
					|| ( tempMax < maxDistance && tempMin > minDistance ) )
				{
					// 지금 구한 구간이 더 좁은 경우에만 교체
					maxDistance = ( maxDistance > tempMax ) ? tempMax : maxDistance;
					minDistance = ( minDistance < tempMin ) ? tempMin : minDistance;
				}
				else
				{
					return false;
				}
			}
		}

		return true;
	}
};

