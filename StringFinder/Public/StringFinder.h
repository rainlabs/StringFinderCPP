// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "CommonTypes.h"
#include <functional>

/* Class for find string in input file */
class StringFinder
{
public:
	StringFinder(const FString& sFile, int iMode = FFile::in);
	~StringFinder();

	// input file is open
	bool IsOpen() const;

	/* find only first match
	* @return uRetLine - line number
	*/
	bool FindString(const FString& sSubString, int iChunkCount, size_t& uRetLine);

	// iterate over all matches
	void FindAllStrings(const FString& sSubString, std::function<void(const FString& sLine, size_t uLine)> fFunction);

protected:
	void ResetFile();
	size_t FileSize();

	FFile m_oFile;
};