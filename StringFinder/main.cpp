// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "CommonTypes.h"
#include "PathFinder.h"
#include "ThreadWorker.h"
#include <chrono>
#include <thread>
#include <future>

int main(int argc, char* argv[])
{
	auto start = std::chrono::system_clock::now();

	Configuration oConfig(argc, argv);
	if (!oConfig.IsValid()) return ErrorCode::INVALID_ARGUMENTS;

	PathFinderPtr pFinder = PathFinder::CreateInstance(oConfig.GetPath(), oConfig.GetFileMask());
	ResultWriterPtr pWriter = ResultWriter::CreateInstance(oConfig.GetOutputFile(), FileFormat::CONSOLE);
	FString sFolder;
	pFinder->Iterate([&](const FString& sFile) {
		ThreadWorker oWorker(oConfig, sFile);
		//std::async(std::launch::async, &ThreadWorker::Run, &oWorker);
		oWorker.Run();
	});

	auto end = std::chrono::system_clock::now();
	auto elapsed = end - start;
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
	COUT << ms.count() / 1000.f << std::endl;
	return ErrorCode::SUCCESS;
}