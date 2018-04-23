// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "CommonTypes.h"
#include "PathFinder.h"
#include "Worker.h"
#include "Measurement.h"
#include "Strings.h"
#include "Logger.h"

int main(int argc, char* argv[])
{
	Configuration oConfig(argc, argv); // Parse arguments

	// Show help and close app normally
	if (oConfig.ShowHelp()) {
		Utils::WriteHelp();
		return ErrorCode::SUCCESS;
	}

	// Construct logger
	LoggerInterface* pLogger = new InfoLogger(nullptr);
	if (oConfig.ShowInfo())
		pLogger = new DebugLogger(pLogger);

	// Check paramenters is valid
	if (!oConfig.IsValid()) {
		pLogger->Info(STR_INVALID_ARGUMENTS);
		delete pLogger;
		return ErrorCode::INVALID_ARGUMENTS;
	}

	// Iterate over all files to find string
	size_t uFoundFiles(0);
	float fDuration = Measurement::Measure([oConfig, &uFoundFiles, &pLogger]() {
		size_t uProcessedFiles(0);

		PathFinderPtr pFinder = PathFinder::CreateInstance(oConfig.GetPath(), oConfig.GetFileMask());
		uFoundFiles = pFinder->Iterate([&](const FString& sFile) {
			if (oConfig.GetOutputFormat() != FileFormat::CONSOLE) {
				pLogger->Debug(_S("Processed: ") + PlatformUtils::StringFormat(std::to_string(++uProcessedFiles)) + _S(" files"));
			}
			Worker oWorker(oConfig, sFile);
			oWorker.Run();
		});
	});

	// Simple measurement result
	pLogger->Debug(STR_NL);
	pLogger->Debug(STR_MEASURE + PlatformUtils::StringFormat(std::to_string(fDuration)));
	pLogger->Debug(STR_FOUND_FILES + PlatformUtils::StringFormat(std::to_string(uFoundFiles)));

	delete pLogger;
	return ErrorCode::SUCCESS;
}
