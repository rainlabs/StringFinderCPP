// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "CommonTypes.h"
#include "PathFinder.h"
#include "Worker.h"
#include "Measurement.h"
#include "Strings.h"

int main(int argc, char* argv[])
{
	Configuration oConfig(argc, argv); // Parse arguments

	// Show help and close app normally
	if (oConfig.ShowHelp()) {
		Utils::WriteHelp();
		return ErrorCode::SUCCESS;
	}

	// Check paramenters is valid
	if (!oConfig.IsValid()) {
		Utils::WriteInConsole(STR_INVALID_ARGUMENTS);
		return ErrorCode::INVALID_ARGUMENTS;
	}

	// Iterate over all files to find string
	size_t uFoundFiles(0);
	float fDuration = Measurement::Measure([oConfig, &uFoundFiles]() {
		size_t uProcessedFiles(0);

		PathFinderPtr pFinder = PathFinder::CreateInstance(oConfig.GetPath(), oConfig.GetFileMask());
		uFoundFiles = pFinder->Iterate([&](const FString& sFile) {
			if (oConfig.ShowInfo() && oConfig.GetOutputFormat() != FileFormat::CONSOLE) {
				COUT << _S("\r") << _S("Processed: ") << ++uProcessedFiles << _S(" files");
			}
			Worker oWorker(oConfig, sFile);
			oWorker.Run();
		});
	});

	// Simple measurement result
	if (oConfig.ShowInfo()) {
		Utils::WriteInConsole(_S("\n"));
		Utils::WriteInConsole(STR_MEASURE, fDuration); 
		Utils::WriteInConsole(STR_FOUND_FILES, uFoundFiles);
	}

	return ErrorCode::SUCCESS;
}
