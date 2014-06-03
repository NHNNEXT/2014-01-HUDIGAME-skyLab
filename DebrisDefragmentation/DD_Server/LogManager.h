#pragma once

#include "LoggerProperties.h"

#define DDLOG_FATAL(MESSAGE) GLogManager->LogFatal(MESSAGE)
#define DDLOG_ERROR(MESSAGE) GLogManager->LogError(MESSAGE)
#define DDLOG_WARN(MESSAGE) GLogManager->LogWarn(MESSAGE)
#define DDLOG_INFO(MESSAGE) GLogManager->LogInfo(MESSAGE)
#define DDLOG_DEBUG(MESSAGE) GLogManager->LogDebug(MESSAGE)

class LogManager
{
public:
	LogManager();
	~LogManager();

	void Init();
	log4cplus::Logger* GetLogger() { return &m_Logger; }

	// 조심해!!
	// 스트링 조합해서 넘겨야 해...
	// 가변인자를 사용해야 하나
	// 문자 스트림을 이용해야 할 듯
	void LogFatal( std::wstring message );
	void LogError( std::wstring message );
	void LogWarn( std::wstring message );
	void LogInfo( std::wstring message );
	void LogDebug( std::wstring message );

	log4cplus::Logger	m_Logger;
};

extern LogManager* GLogManager;