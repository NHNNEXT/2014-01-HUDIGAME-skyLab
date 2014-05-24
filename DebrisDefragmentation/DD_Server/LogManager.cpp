#include "stdafx.h"
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
	
	
	/*
	helpers::LogLog::getLogLog()->setInternalDebugging( true );
	SharedAppenderPtr append_1( new RollingFileAppender( LOG4CPLUS_TEXT( "Test.log" ), 5 * 1024, 5 ) );
	append_1->setName( LOG4CPLUS_TEXT( "First" ) );
	append_1->setLayout( std::auto_ptr<Layout>( new TTCCLayout() ) );
	Logger::getRoot().addAppender( append_1 );

	Logger root = Logger::getRoot();
	Logger test = Logger::getInstance( LOG4CPLUS_TEXT( "test" ) );
	Logger subTest = Logger::getInstance( LOG4CPLUS_TEXT( "test.subtest" ) );

	for ( int i = 0; i < 10; ++i ) {
		NDCContextCreator _context( LOG4CPLUS_TEXT( "loop" ) );
		LOG4CPLUS_DEBUG( subTest, "Entering loop #" << i );
	}
	*/
}

void LogManager::Log( std::wstring message )
{
	LOG4CPLUS_INFO( m_Logger, message.c_str() );
}