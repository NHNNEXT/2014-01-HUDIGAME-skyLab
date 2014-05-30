#include "stdafx.h"
#include "Exception.h"
#include "client/windows/handler/exception_handler.h"
#include "client/windows/sender/crash_report_sender.h"

LONG WINAPI ExceptionFilter( EXCEPTION_POINTERS* exceptionInfo )
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof( si );
	si.lpTitle = L"exception handler";
	wchar_t command[] = L"crash_generation_app.exe";
	CreateProcess( NULL, command, NULL, NULL, TRUE,
				   CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi );
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
	Sleep( 500 );

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
	
// 	Sleep( 500 );
// 	TerminateProcess( pi.hProcess, 0 );
	
	// 예외처리 종료 신호 반환
	return EXCEPTION_EXECUTE_HANDLER;

}