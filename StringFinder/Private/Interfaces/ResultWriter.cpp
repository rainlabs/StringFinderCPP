// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "ResultWriter.h"
#include "../ResultWriters/PlainResultWriter.h"
#include "../ResultWriters/ConsoleResultWriter.h"

ResultWriterPtr ResultWriter::CreateInstance(const FString& sFile, FileFormat eFormat)
{
	switch (eFormat) {
	case FileFormat::PLAIN_TEXT:
		return std::make_shared<PlainResultWriter>(PlainResultWriter(sFile));
	case FileFormat::MARKDOWN:
		break;
	}
	
	return std::make_shared<ConsoleResultWriter>(ConsoleResultWriter(sFile));
}
