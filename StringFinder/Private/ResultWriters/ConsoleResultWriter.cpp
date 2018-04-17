// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "ConsoleResultWriter.h"

ConsoleResultWriter::ConsoleResultWriter(const ConsoleResultWriter & oCopy) :
	ResultWriter(oCopy),
	m_sSegment(_S(""))
{
}

ConsoleResultWriter::~ConsoleResultWriter()
{
	if (m_oStream.tellp() > 0) {
		Commit();
	}
}

void ConsoleResultWriter::SetSegment(const FString & sSegment)
{
	m_sSegment = sSegment;
}

void ConsoleResultWriter::Write(const FString & sOutput, size_t uPos)
{
	m_oStream << sOutput << _S(":") << uPos << std::endl;
}

bool ConsoleResultWriter::Commit()
{
	if (!IsOpen()) return false;

	if(!m_sSegment.empty())
		COUT << _S("File: ") << m_sSegment << std::endl;
	COUT << m_oStream.str();

	m_oStream.str(FString()); // Clear
	return true;
}

ConsoleResultWriter::ConsoleResultWriter(const FString & sFile) :
	ResultWriter(sFile),
	m_sSegment(_S(""))
{
}
