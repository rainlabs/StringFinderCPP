// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "PlainResultWriter.h"
#include "Strings.h"

PlainResultWriter::PlainResultWriter(const PlainResultWriter & oCopy) :
	ResultWriter(oCopy),
	m_oFile(oCopy.m_sFilename, FFile::out | FFile::app),
	m_sSegment(STR_EMPTY),
	m_sFilename(oCopy.m_sFilename)
{
}

PlainResultWriter::~PlainResultWriter()
{
	if (IsOpen()) {
		if (m_oStream.tellp() > 0) {
			Commit();
		}

		m_oFile.close();
	}
}

void PlainResultWriter::SetSegment(const FString & sSegment)
{
	m_sSegment = sSegment;
}

void PlainResultWriter::Write(const FString & sOutput, size_t uPos)
{
	m_oStream << STR_TAB << uPos << STR_DELIMETER << sOutput << std::endl;
	
}

bool PlainResultWriter::Commit()
{
	if (!IsOpen()) return false;
	if (m_oStream.tellp() < 1) return false;

	if(!m_sSegment.empty())
		m_oFile << STR_SEGMENT_HEADER << m_sSegment << std::endl;
	m_oFile << m_oStream.str();

	m_oStream.str(FString()); // Clear buffer
	return true;
}

PlainResultWriter::PlainResultWriter(const FString & sFile) :
	ResultWriter(sFile),
	m_oFile(sFile, FFile::out | FFile::app),
	m_sSegment(STR_EMPTY),
	m_sFilename(sFile)
{
}
