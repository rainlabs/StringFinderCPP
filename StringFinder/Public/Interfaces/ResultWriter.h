// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "CommonTypes.h"
#include <memory>

class ResultWriter;
typedef std::shared_ptr<ResultWriter> ResultWriterPtr;

/* Output writer interface */
class ResultWriter
{
public:
	// Create instance by format
	static ResultWriterPtr CreateInstance(const FString& sFile, FileFormat eFormat = FileFormat::PLAIN_TEXT);

	virtual ~ResultWriter() {};

	// Set first segment in write block(i.e. filename)
	virtual void SetSegment(const FString& sSegment) = 0;

	// Write in buffer found string
	virtual void Write(const FString& sOutput, size_t uPos) = 0;

	// Write all into file
	virtual bool Commit() = 0;

	// Check file already is open
	virtual bool IsOpen() = 0;

protected:
	ResultWriter(const FString& sFile) {};
};