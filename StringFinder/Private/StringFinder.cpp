// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "StringFinder.h"

StringFinder::StringFinder(const FString & sFile, int iMode) :
	m_oFile(sFile, iMode)
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

bool StringFinder::FindString(const FString & sSubString, int iChunkCount, size_t& uRetLine)
{
	if (!IsOpen()) return false;

	size_t uLine(0);

	// read line by line
	if (iChunkCount == 0) {
		FString sReadLine;
		while (std::getline(m_oFile, sReadLine)) {
			uLine++;
			size_t uFound = sReadLine.find(sSubString);
			if (uFound != FString::npos) {
				ResetFile();
				uRetLine = uLine;
				return true;
			}
		}

		return false;
	}

	size_t uFileSize = FileSize();
	if (uFileSize < sSubString.size()) return false;

	size_t uBufferSize = sSubString.size() * iChunkCount;
	if (uBufferSize > uFileSize)
		uBufferSize = uFileSize;

	// Read block by block
	FString sBuffer(uBufferSize, _S('\0'));
	size_t uStep = uBufferSize - (sSubString.size() - 1);
	for (size_t uOffset = 0; uOffset <= uFileSize - sSubString.size(); uOffset+= uStep) {
		size_t uTempFound(0);
		m_oFile.seekg(uOffset);
		m_oFile.read((FChar*)&sBuffer[0], uBufferSize);

		// Find all new lines in block
		while ((uTempFound = sBuffer.find_first_of(_S('\n'), uTempFound)) != FString::npos) {
			uTempFound++;
			uLine++;
		}

		size_t uFound = sBuffer.find(sSubString);
		if (uFound != FString::npos) {
			ResetFile();
			uRetLine = uLine; // TODO: it's incorrect line number, should be range lines
			return true;
		}

		// erase buffer
		std::fill(sBuffer.begin(), sBuffer.end(), _S('\0'));
	}

	ResetFile();
	return false;
}

void StringFinder::FindAllStrings(const FString & sSubString, std::function<void(const FString& sLine, size_t uLine)> fFunction)
{
	if (!IsOpen()) return;

	size_t uLine(0);
	FString sReadLine;

	while (std::getline(m_oFile, sReadLine)) {
		uLine++;
		size_t uFound = sReadLine.find(sSubString);
		if (uFound != FString::npos) {
			fFunction(sReadLine, uLine);
		}
	}
}

void StringFinder::ResetFile()
{
	m_oFile.clear();
	m_oFile.seekg(0, std::ios::beg);
}

size_t StringFinder::FileSize()
{
	size_t uSize(0);
	m_oFile.seekg(0, std::ios::end);
	uSize = m_oFile.tellg();
	m_oFile.seekg(0, std::ios::beg);

	return uSize;
}
