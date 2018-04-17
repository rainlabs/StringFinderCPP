// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "CommonTypes.h"
#include "Configuration.h"
#include "ResultWriter.h"
#include "StringFinder.h"

/* Worker finder class (can be used for multithreading) */
class Worker
{
public:
	Worker(const Configuration& oConfig, const FString& sFile);

	// Find string in file and write into output
	void Run();

protected:
	FString m_sFile;
	ResultWriterPtr m_pResultWriter;
	StringFinder m_oStringFinder;
	Configuration m_oConfig;
};