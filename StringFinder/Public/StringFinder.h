// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "CommonTypes.h"
#include <functional>

class StringFinder
{
public:
	StringFinder(const FString& sFile);
	~StringFinder();

	bool IsOpen() const;
	size_t FindString(const FString& sSubString);
	void FindAllStrings(const FString& sSubString, std::function<void(const FString& sLine, size_t uLine)> fFunction);

protected:
	void ResetFile();

	FFile m_oFile;
};