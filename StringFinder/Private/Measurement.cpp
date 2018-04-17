// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "Measurement.h"

float Measurement::Measure(std::function<void()> fFunction)
{
	auto tStart = std::chrono::system_clock::now();

	fFunction();

	auto tElapsed = std::chrono::system_clock::now() - tStart;
	std::chrono::milliseconds tElapsedMS = std::chrono::duration_cast<std::chrono::milliseconds>(tElapsed);
	return tElapsedMS.count() / 1000.f;
}
