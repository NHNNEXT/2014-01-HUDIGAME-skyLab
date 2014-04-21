#pragma once

LONG WINAPI ExceptionFilter( EXCEPTION_POINTERS* exceptionInfo );

inline void CRASH_ASSERT( bool isOk )
{
	if ( isOk )
		return;

	// 메모리 주소 0에 강제로 접근해서 에러 발생 유도
	int* crashVal = 0;
	*crashVal = 0xDEADBEEF;
}
