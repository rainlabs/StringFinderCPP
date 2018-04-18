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
	// Write message into console
	static inline void WriteInConsole(const FString& sError) {
		if (sError.empty()) return;

		COUT << sError << std::endl;
	};

	// Write message into console with value
	template<typename T>
	static inline void WriteInConsole(const FString& sError, T code) {
		if (sError.empty()) return;

		COUT << sError << code << std::endl;
    }

	static void WriteHelp() {
		COUT << _S("Simple StringFinder help: ") << std::endl;
		COUT << _S("-p") << _S("\t") << _S("- Path") << std::endl;
		COUT << _S("-m") << _S("\t") << _S("- File mask") << std::endl;
		COUT << _S("-p") << _S("\t") << _S("- Path") << std::endl;
		COUT << _S("-i") << _S("\t") << _S("- File with search string") << std::endl;
		COUT << _S("-s") << _S("\t") << _S("- Search string") << std::endl;
		COUT << _S("-o") << _S("\t") << _S("- Output file (write to console otherwise)") << std::endl;
		COUT << _S("-a") << _S("\t") << _S("- Extended output (with lines and line numbers)") << std::endl;
		COUT << _S("-d") << _S("\t") << _S("- Show stat info (time and file numbers)") << std::endl;
		COUT << _S("-h") << _S("\t") << _S("- Show this help") << std::endl;
	}

    // trim from end (like \n in unix file)
    static inline void rtrim(FString &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](FChar ch) {
            return ch != _S('\n'); // TODO: std::isspace
        }).base(), s.end());
    }
};
