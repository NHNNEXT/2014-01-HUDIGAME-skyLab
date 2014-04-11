#include "stdafx.h"
#include "DDPoint.h"

DDPoint& DDPoint::operator=( const DDPoint& point )
{
	this->SetPoint( point.GetX(), point.GetY() );
	return *this;
}

DDPoint DDPoint::operator+( const DDPoint& point ) const
{
	return DDPoint( this->m_X + point.GetX(), this->m_Y + point.GetY() );
}

DDPoint DDPoint::operator-( const DDPoint& point ) const
{
	return DDPoint( this->m_X - point.GetX(), this->m_Y - point.GetY() );
}

DDPoint DDPoint::operator-( ) const
{
	return DDPoint( -this->m_X, -this->m_Y );
}

DDPoint DDPoint::operator*( float n ) const
{
	return DDPoint( this->m_X * n, this->m_Y * n );
}

DDPoint DDPoint::operator/( float n ) const
{
	return DDPoint( this->m_X / n, this->m_Y / n );
}