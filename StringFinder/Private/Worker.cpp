// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "Worker.h"

Worker::Worker(const Configuration & oConfig, const FString & sFile) :
	m_sFile(sFile),
	m_oStringFinder(sFile),
	m_pResultWriter(ResultWriter::CreateInstance(oConfig.GetOutputFile(), oConfig.GetOutputFormat())),
	m_oConfig(oConfig)
{
	m_pResultWriter->SetSegment(sFile);
}

void Worker::Run()
{
	m_oStringFinder.FindAllStrings(m_oConfig.GetFindString(), [&](const FString sLine, size_t uLine) {
		m_pResultWriter->Write(sLine, uLine);
	});

	m_pResultWriter->Commit();
}
