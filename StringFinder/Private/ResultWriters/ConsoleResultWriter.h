// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "ResultWriter.h"

class ConsoleResultWriter : public ResultWriter
{
public:
	ConsoleResultWriter(const ConsoleResultWriter& oCopy);
	virtual ~ConsoleResultWriter();

	virtual void SetSegment(const FString& sSegment) override;
	virtual void Write(const FString& sOutput, size_t uPos) override;
	virtual bool Commit() override;
	inline virtual bool IsOpen() override { return true; };

protected:
	friend class ResultWriter;
	ConsoleResultWriter(const FString& sFile);

private:
	FString m_sSegment;
	FStringStream m_oStream;
};