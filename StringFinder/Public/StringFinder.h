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
	StringFinder(const FString& sFile);
	~StringFinder();

	// input file is open
	bool IsOpen() const;

	// find only first match
	size_t FindString(const FString& sSubString);

	// iterate over all matches
	void FindAllStrings(const FString& sSubString, std::function<void(const FString& sLine, size_t uLine)> fFunction);

protected:
	void ResetFile();

	FFile m_oFile;
};