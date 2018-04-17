// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "CommonTypes.h"
#include "Configuration.h"
#include "ResultWriter.h"
#include "StringFinder.h"

class ThreadWorker
{
public:
	ThreadWorker(const Configuration& oConfig, const FString& sFile);

	void Run();

protected:
	FString m_sFile;
	ResultWriterPtr m_pResultWriter;
	StringFinder m_oStringFinder;
	Configuration m_oConfig;
};