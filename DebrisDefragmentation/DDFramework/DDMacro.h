#pragma once

typedef D3DXVECTOR3 DDVECTOR3;

template <typename T>
inline void SafeDelete( T* &p )
{
	if ( p != nullptr )
	{
		delete p;
		p = nullptr;
	}
}

