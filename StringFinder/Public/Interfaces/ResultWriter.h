// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "CommonTypes.h"
#include <memory>

class ResultWriter;
typedef std::shared_ptr<ResultWriter> ResultWriterPtr;

class ResultWriter
{
public:
	static ResultWriterPtr CreateInstance(const FString& sFile, FileFormat eFormat = FileFormat::PLAIN_TEXT);

	virtual ~ResultWriter() {};
	virtual void SetSegment(const FString& sSegment) = 0;
	virtual void Write(const FString& sOutput, size_t uPos) = 0;
	virtual bool Commit() = 0;
	virtual bool IsOpen() = 0;

protected:
	ResultWriter(const FString& sFile) {};
};