#include "stdafx.h"
#include "Exception.h"
#include "client/windows/handler/exception_handler.h"
#include "client/windows/sender/crash_report_sender.h"

LONG WINAPI ExceptionFilter( EXCEPTION_POINTERS* exceptionInfo )
{
	static int kCustomInfoCount = 2;
	static google_breakpad::CustomInfoEntry kCustomInfoEntries[] = {
		google_breakpad::CustomInfoEntry( L"prod", L"CrashTestApp" ),
		google_breakpad::CustomInfoEntry( L"ver", L"1.0" ),
	};

	google_breakpad::CustomClientInfo custom_info = { kCustomInfoEntries, kCustomInfoCount };
	const wchar_t kPipeName[] = L"\\\\.\\pipe\\BreakpadCrashServices\\TestServer";

	google_breakpad::CrashGenerationClient client( kPipeName, MiniDumpNormal, &custom_info );
	client.Register();
	client.RequestDump( exceptionInfo );
	client.RequestUpload(10);
	

	// 예외처리 종료 신호 반환
	return EXCEPTION_EXECUTE_HANDLER;

}