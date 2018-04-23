// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "Logger.h"
#include "Strings.h"

LoggerDecorator::LoggerDecorator(LoggerInterface * pLogger) :
	LoggerInterface(),
	m_pLoggerWrappee(pLogger)
{
}

LoggerDecorator::~LoggerDecorator()
{
	if (m_pLoggerWrappee)
		delete m_pLoggerWrappee;
}

void LoggerDecorator::Info(const FString & sLog)
{
	if (m_pLoggerWrappee)
		m_pLoggerWrappee->Info(sLog);
}

void LoggerDecorator::Debug(const FString & sLog)
{
	if (m_pLoggerWrappee)
		m_pLoggerWrappee->Debug(sLog);
}

InfoLogger::InfoLogger(LoggerInterface * pLogger) :
	LoggerDecorator(pLogger)
{
}

InfoLogger::~InfoLogger()
{
}

void InfoLogger::Info(const FString & sLog)
{
	LoggerDecorator::Info(sLog);
	COUT << STR_INFO_LOG << sLog << std::endl;
}

DebugLogger::DebugLogger(LoggerInterface * pLogger) :
	LoggerDecorator(pLogger)
{
}

DebugLogger::~DebugLogger()
{
}

void DebugLogger::Debug(const FString & sLog)
{
	LoggerDecorator::Debug(sLog);
	COUT << STR_DEBUG_LOG << sLog << std::endl;
}
