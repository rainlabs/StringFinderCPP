// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "CommonTypes.h"

/* Logger interface class */
class LoggerInterface
{
public:
	virtual ~LoggerInterface() {};
	virtual void Info(const FString& sLog) = 0;
	virtual void Debug(const FString& sLog) = 0;
};

/* Logger Decoration, Call wrappee methods */
class LoggerDecorator : public LoggerInterface
{
public:
	LoggerDecorator(LoggerInterface* pLogger);
	virtual ~LoggerDecorator();
	virtual void Info(const FString& sLog);
	virtual void Debug(const FString& sLog);

private:
	LoggerInterface * m_pLoggerWrappee;
};

/* Info logger implementation */
class InfoLogger : public LoggerDecorator
{
public:
	InfoLogger(LoggerInterface* pLogger);
	virtual ~InfoLogger();
	virtual void Info(const FString& sLog);
};

/* Debug logger implementation */
class DebugLogger : public LoggerDecorator
{
public:
	DebugLogger(LoggerInterface* pLogger);
	virtual ~DebugLogger();
	virtual void Debug(const FString& sLog);
};