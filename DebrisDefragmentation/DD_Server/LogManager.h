#pragma once

#include "LoggerProperties.h"

class LogManager
{
public:
	LogManager();
	~LogManager();

	void Init();
	log4cplus::Logger* GetLogger() { return &m_Logger; }

	void Log( std::wstring message );

private:
	log4cplus::Logger m_Logger;
};

extern LogManager* GLogManager;