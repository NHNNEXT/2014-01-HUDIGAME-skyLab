#pragma once

/*
	작성자 : 최경욱
	작성일 : 2014. 4. 6
	내용 : 평면상의 좌표를 표현하고 연산하는 데이터 타입 정의 (NNGameFramework와 동일)
*/

#include "DDConfig.h"
#include <math.h>

class DDPoint
{
public:
	DDPoint() : m_X( 0.f ), m_Y( 0.f ) {}
	DDPoint( float x, float y ) : m_X( x ), m_Y( y ) {}
	DDPoint( DDPoint& point ) : m_X( point.GetX() ), m_Y( point.GetY() ) {}
	~DDPoint() {}

	DDPoint& operator= ( const DDPoint& point );
	DDPoint operator+( const DDPoint& point ) const;
	DDPoint operator-( const DDPoint& point ) const;
	DDPoint operator-( ) const;
	DDPoint operator*( float n ) const;
	DDPoint operator/( float n ) const;

	/*
		input : DDPoint 2개(시작점, 끝점), float 가중치
		output : 인자로 받은 두 점을 잇는 선분 위의 점들 중 가중치를 적용한 linear interpolation 지점의 좌표
		주의 : 가중치 t는 0과 1 사이의 값을 가진다.
	*/
	DDPoint DDPoint::Lerp( const DDPoint& startPoint, const DDPoint& endPoint, float t )
	{
		return DDPoint( t * startPoint.GetX() + ( 1 - t ) * endPoint.GetX()
			, t * startPoint.GetY() + ( 1 - t ) * endPoint.GetY() );
	}

	/*
		input : 거리를 알고 싶은 DDPoint
		output : 주어진 점과 떨어진 거리
	*/
	inline float GetDistance( DDPoint& point ) const {
		return sqrtf( pow( m_X - point.GetX(), 2 ) + pow( m_Y - point.GetY(), 2 ) );
	}

	/*
		input : 거리를 알고 싶은 점의 x좌표와 y좌표
		output : 주어진 점과 떨어진 거리
	*/
	inline float GetDistance( float x, float y ) const {
		return sqrtf( pow( m_X - x, 2 ) + pow( m_Y - y, 2 ) );
	}

	inline float GetX() const { return m_X; }
	inline float GetY() const { return m_Y; }

	void SetPoint( float x, float y ) {
		m_X = x;
		m_Y = y;
	}

	void SetPoint( DDPoint& point ) { *this = point; }

	void SetX( float x ) { m_X = x; }

	void SetY( float y ) { m_Y = y; }


private:
	float m_X, m_Y;
};

