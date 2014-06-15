#pragma once

namespace DDMath
{	
	float	GetRandomFloat( float lowBound, float highBound );	
	void	GetRandomVector(D3DXVECTOR3* out,	D3DXVECTOR3* min,	D3DXVECTOR3* max );
	DWORD	FtoDw( float f );
}