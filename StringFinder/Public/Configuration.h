// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "CommonTypes.h"

class Configuration
{
public:
	Configuration();
	Configuration(int argc, char * argv[]);
	~Configuration();

	void Initialize(int argc, char * argv[]);
	FString GetPath() const;
	FString GetFileMask() const;
	FString GetFindString() const;
	FString GetOutputFile() const;
	FileFormat GetOutputFormat() const;
	bool IsValid() const;

	friend FStream & operator<<(FStream & oStream, const Configuration & oConfig);

protected:
	FString ReadFindString(const FString & sFile) const;

private:
	FString m_sPath;
	FString m_sFileMask;
	FString m_sFindString;
	FString m_sOutputFile;
	bool m_bValidOutputFile;
};