﻿#include "stdafx.h"
#include "LogManager.h"
#include <log4cplus/helpers/loglog.h>

#pragma comment(lib,"log4cplusUD.lib")

using namespace log4cplus;

LogManager* GLogManager = nullptr;

LogManager::LogManager()
{
}

LogManager::~LogManager()
{
}

void LogManager::Init()
{
	log4cplus::initialize();

	log4cplus::SharedAppenderPtr consoleAppender( new log4cplus::ConsoleAppender() );
	consoleAppender->setName( L"ConsoleAppender" );
	std::auto_ptr<log4cplus::Layout> consoleLayout = std::auto_ptr<log4cplus::Layout>( new log4cplus::TTCCLayout() );
	consoleAppender->setLayout( consoleLayout );

	log4cplus::SharedAppenderPtr fileAppender( new log4cplus::FileAppender( L"DebriDefragmentationServer.log" ) );
	fileAppender->setName( L"FileAppender" );
	std::auto_ptr<log4cplus::Layout> fileLayout = std::auto_ptr<log4cplus::Layout>( new log4cplus::TTCCLayout() );
	fileAppender->setLayout( fileLayout );
	
	m_Logger = log4cplus::Logger::getInstance( L"myLoggerName" );
	m_Logger.addAppender( consoleAppender );
	m_Logger.addAppender( fileAppender );

	m_Logger.setLogLevel( log4cplus::INFO_LOG_LEVEL );
}

void LogManager::LogFatal( std::wstring message )
{
	LOG4CPLUS_FATAL( m_Logger, message.c_str() );
}

void LogManager::LogError( std::wstring message )
{
	LOG4CPLUS_ERROR( m_Logger, message.c_str() );
}

void LogManager::LogWarn( std::wstring message )
{
	LOG4CPLUS_WARN( m_Logger, message.c_str() );
}

void LogManager::LogInfo( std::wstring message )
{
	LOG4CPLUS_INFO( m_Logger, message.c_str() );
}

void LogManager::LogDebug( std::wstring message )
{
	LOG4CPLUS_DEBUG( m_Logger, message.c_str() );
}