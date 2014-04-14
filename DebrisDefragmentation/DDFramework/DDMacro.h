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

template <class T>
class Singleton
{
protected:
	Singleton( void ) {}
	virtual ~Singleton( void ) {}
public:
	static T* GetInstance( void )
	{
		if ( !m_pInstance )
		{
			m_pInstance = new T;
		}
		return m_pInstance;
	}

	static void ReleaseInstance( void )
	{
		SafeDelete( m_pInstance );
	}

private:
	static T*	m_pInstance;
};
template <typename T>
T* Singleton<T>::m_pInstance = nullptr;