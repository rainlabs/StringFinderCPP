// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "CommonTypes.h"

class StringFinder
{
public:
	StringFinder(const FString& sFile);
	~StringFinder();

	bool IsOpen() const;
	size_t FindString(const FString& sSubString);

protected:
	void ResetFile();

	FFile m_oFile;
};