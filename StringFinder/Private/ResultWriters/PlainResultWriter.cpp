// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "PlainResultWriter.h"

PlainResultWriter::PlainResultWriter(const PlainResultWriter & oCopy) :
	ResultWriter(oCopy),
	m_oFile(oCopy.m_sFilename, FFile::out | FFile::app),
	m_sSegment(_S("")),
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
	m_oStream << _S("\t") << sOutput << _S(":") << uPos << std::endl;
	
}

bool PlainResultWriter::Commit()
{
	if (!IsOpen()) return false;

	if(!m_sSegment.empty())
		m_oFile << _S("File: ") << m_sSegment << std::endl;
	m_oFile << m_oStream.str();

	m_oStream.str(FString()); // Clear
	return true;
}

PlainResultWriter::PlainResultWriter(const FString & sFile) :
	ResultWriter(sFile),
	m_oFile(sFile, FFile::out | FFile::app),
	m_sSegment(_S("")),
	m_sFilename(sFile)
{
}
