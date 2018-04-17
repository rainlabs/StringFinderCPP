// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "StringFinder.h"

StringFinder::StringFinder(const FString & sFile) :
	m_oFile(sFile, FFile::in)
{
}

StringFinder::~StringFinder()
{
	if (IsOpen()) {
		m_oFile.close();
	}
}

bool StringFinder::IsOpen() const
{
	return m_oFile.is_open();
}

size_t StringFinder::FindString(const FString & sSubString)
{
	if (!IsOpen()) return 0;

	size_t uLine(0);
	FString sReadLine;

	while (std::getline(m_oFile, sReadLine)) {
		uLine++;
		size_t uFound = sReadLine.find(sSubString);
		if (uFound != FString::npos) {
			ResetFile();
			return uLine;
		}
	}

	ResetFile();
	return 0;
}

void StringFinder::ResetFile()
{
	m_oFile.clear();
	m_oFile.seekg(0, std::ios::beg);
}
