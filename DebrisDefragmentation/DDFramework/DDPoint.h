#pragma once


/*
	�ۼ��� : �ְ��
	�ۼ��� : 2014. 4. 6
	���� : ������ ��ǥ�� ǥ���ϰ� �����ϴ� ������ Ÿ�� ���� (NNGameFramework�� ����)
*/

#include "DDConfig.h"
// agebreak : ���� ���̰�, ������ �ʴ� ����� PreCompiled Header�� �ִ°� ����.
// pre-compiled header�� �̵�

class DDPoint
{
public:
	DDPoint() : m_X( 0.f ), m_Y( 0.f ) {}
	DDPoint( float x, float y ) : m_X( x ), m_Y( y ) {}
	DDPoint( const DDPoint& point ) : m_X( point.GetX() ), m_Y( point.GetY() ) {} // agebreak : �������ϸ� ��ǥ�� Ȯ���̶�鼭 ������ �߻���. �̰��� ��ƶ�. �����Ƿ� ������ �˷���. 
	~DDPoint() {}

	// agebreak : �Ʒ��� ���� �����ϰ� ���� ���� �Լ���, inline���� �����Ѵ�
	// inline���� ���� �Ϸ�
	DDPoint& operator=( const DDPoint& point ) { this->SetPoint( point.GetX(), point.GetY() ); return *this; }
	DDPoint operator+( const DDPoint& point ) const { return DDPoint( this->m_X + point.GetX(), this->m_Y + point.GetY() );}
	DDPoint operator-( const DDPoint& point ) const { return DDPoint( this->m_X - point.GetX(), this->m_Y - point.GetY() );}
	DDPoint operator-( ) const { return DDPoint( -this->m_X, -this->m_Y ); }
	DDPoint operator*( float n ) const { return DDPoint( this->m_X * n, this->m_Y * n ); }
	DDPoint operator/( float n ) const { return DDPoint( this->m_X / n, this->m_Y / n ); }

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
		// agebreak : �ΰ��� �����ε��� �Լ��� �Ʒ��� ���� �ϳ��� �����ؼ� ����ϴ� ���� ����
		//return sqrtf( pow( m_X - point.GetX(), 2 ) + pow( m_Y - point.GetY(), 2 ) );
		return GetDistance(point.GetX(), point.GetY());
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

