// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "ThreadWorker.h"

ThreadWorker::ThreadWorker(const Configuration & oConfig, const FString & sFile) :
	m_sFile(sFile),
	m_oStringFinder(sFile),
	m_pResultWriter(ResultWriter::CreateInstance(oConfig.GetOutputFile(), oConfig.GetOutputFormat())),
	m_oConfig(oConfig)
{
	m_pResultWriter->SetSegment(sFile);
}

void ThreadWorker::Run()
{
	size_t uLine = m_oStringFinder.FindString(m_oConfig.GetFindString());
	if (uLine > 0) {
		m_pResultWriter->Write(m_sFile, uLine);
		m_pResultWriter->Commit();
	}
}
