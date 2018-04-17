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
	Configuration oConfig(argc, argv);
	if (!oConfig.IsValid()) {
		Utils::WriteInConsole(STR_INVALID_ARGUMENTS);
		return ErrorCode::INVALID_ARGUMENTS;
	}

	float fDuration = Measurement::Measure([oConfig]() {
		PathFinderPtr pFinder = PathFinder::CreateInstance(oConfig.GetPath(), oConfig.GetFileMask());
		pFinder->Iterate([&](const FString& sFile) {
			Worker oWorker(oConfig, sFile);
			oWorker.Run();
		});
	});

	Utils::WriteInConsole(STR_MEASURE, fDuration);
	return ErrorCode::SUCCESS;
}