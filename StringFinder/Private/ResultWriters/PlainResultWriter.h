// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "ResultWriter.h"

class PlainResultWriter : public ResultWriter
{
public:
	PlainResultWriter(const PlainResultWriter& oCopy);
	virtual ~PlainResultWriter();

	virtual void SetSegment(const FString& sSegment) override;
	virtual void Write(const FString& sOutput, size_t uPos) override;
	virtual bool Commit() override;
	inline virtual bool IsOpen() override { return m_oFile.is_open(); };

protected:
	friend class ResultWriter;
	PlainResultWriter(const FString& sFile);

private:
	FFile m_oFile;             // Output file
	FString m_sSegment;        // Saved segment
	FStringStream m_oStream;   // Write buffer

	FString m_sFilename;       // Output file name
};