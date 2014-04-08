#pragma once

template <typename T>
inline void SafeDelete( T* &p )
{
	if ( p != nullptr )
	{
		delete p;
		p = nullptr;
	}
}

template <typename T>
inline void SafeArrayDelete( T* &p )
{
	if ( p != nullptr )
	{
		delete[] p;
		p = nullptr;
	}
}

#define CREATE_FUNC(CLASS_NAME) \
	static CLASS_NAME* Create() \
{ \
	CLASS_NAME* pInstance = new CLASS_NAME(); \
	return pInstance; \
}