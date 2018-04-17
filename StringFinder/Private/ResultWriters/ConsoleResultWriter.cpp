// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "ConsoleResultWriter.h"
#include "Strings.h"

ConsoleResultWriter::ConsoleResultWriter(const ConsoleResultWriter & oCopy) :
	ResultWriter(oCopy),
	m_sSegment(STR_EMPTY)
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
	m_oStream << STR_TAB << uPos << STR_DELIMETER << sOutput << std::endl;
}

bool ConsoleResultWriter::Commit()
{
	if(!m_sSegment.empty())
		COUT << STR_SEGMENT_HEADER << m_sSegment << std::endl;
	COUT << m_oStream.str();

	m_oStream.str(FString()); // Clear
	return true;
}

ConsoleResultWriter::ConsoleResultWriter(const FString & sFile) :
	ResultWriter(sFile),
	m_sSegment(STR_EMPTY)
{
}
