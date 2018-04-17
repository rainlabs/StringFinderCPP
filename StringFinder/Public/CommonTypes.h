// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "PlatformTypes.h"
#include <algorithm>
#include <iterator>

// Available file formats
enum class FileFormat : unsigned short
{
	PLAIN_TEXT, // file output
	CONSOLE     // raw output
};

// Common Error codes
enum ErrorCode
{
	SUCCESS = 0,
	INVALID_ARGUMENTS
};

// Helper function to output info into console
struct Utils
{
	static void WriteInConsole(const FString& sError) {
		if (sError.empty()) return;

		COUT << sError << std::endl;
	};

	template<typename T>
	static void WriteInConsole(const FString& sError, T code) {
		if (sError.empty()) return;

		COUT << sError << code << std::endl;
	};
};