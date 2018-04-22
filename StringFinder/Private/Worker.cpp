// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "Worker.h"

Worker::Worker(const Configuration & oConfig, const FString & sFile) :
	m_sFile(sFile),
	m_oStringFinder(sFile, oConfig.GetOpenMode()),
	m_pResultWriter(ResultWriter::CreateInstance(oConfig.GetOutputFile(), oConfig.GetOutputFormat())),
	m_oConfig(oConfig)
{
	m_pResultWriter->SetSegment(sFile);
}

void Worker::Run()
{
	if (m_oConfig.IsExtendedOutput()) {
		bool bFound(false);
		m_oStringFinder.FindAllStrings(m_oConfig.GetFindString(), [&](const FString sLine, size_t uLine) {
			m_pResultWriter->Write(sLine, uLine);
			bFound = true;
		});

		if(bFound)
			m_pResultWriter->Commit();
	}
	else {
		size_t uLine(0);
		if (m_oStringFinder.FindString(m_oConfig.GetFindString(), m_oConfig.GetChunkCount(), uLine)) {
			m_pResultWriter->Commit();
		}
	}
}
