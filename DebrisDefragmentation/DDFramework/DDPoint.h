#pragma once

/*
	�ۼ��� : �ְ��
	�ۼ��� : 2014. 4. 6
	���� : ������ ��ǥ�� ǥ���ϰ� �����ϴ� ������ Ÿ�� ���� (NNGameFramework�� ����)
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
		input : DDPoint 2��(������, ����), float ����ġ
		output : ���ڷ� ���� �� ���� �մ� ���� ���� ���� �� ����ġ�� ������ linear interpolation ������ ��ǥ
		���� : ����ġ t�� 0�� 1 ������ ���� ������.
	*/
	DDPoint DDPoint::Lerp( const DDPoint& startPoint, const DDPoint& endPoint, float t )
	{
		return DDPoint( t * startPoint.GetX() + ( 1 - t ) * endPoint.GetX()
			, t * startPoint.GetY() + ( 1 - t ) * endPoint.GetY() );
	}

	/*
		input : �Ÿ��� �˰� ���� DDPoint
		output : �־��� ���� ������ �Ÿ�
	*/
	inline float GetDistance( DDPoint& point ) const {
		return sqrtf( pow( m_X - point.GetX(), 2 ) + pow( m_Y - point.GetY(), 2 ) );
	}

	/*
		input : �Ÿ��� �˰� ���� ���� x��ǥ�� y��ǥ
		output : �־��� ���� ������ �Ÿ�
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

