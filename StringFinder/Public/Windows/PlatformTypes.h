// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

typedef std::wstring FString;               // Base string
typedef std::wostream FStream;              // Base ostream
typedef std::wfstream FFile;                // Base file
typedef std::wstringstream FStringStream;   // Base stringstream
typedef wchar_t FChar;                      // Base char

#define _S(text) L ## text                  // Decorate string
#define COUT std::wcout                     // Base cout

/* Platform specifiec utils */
class PlatformUtils
{
public:
	// Convert raw string into wstring
	static inline FString StringFormat(const std::string& sIn) {
		FString sOutput(sIn.size(), '\0');
		auto& f = std::use_facet<std::codecvt<FChar, char, std::mbstate_t>>(std::locale());
		std::mbstate_t mbState = std::mbstate_t();

		const char* sFromText;
		wchar_t* sOutText;
		f.in(mbState, &sIn[0], &sIn[sIn.size()], sFromText,
			&sOutput[0], &sOutput[sOutput.size()], sOutText);
		sOutput.resize(sOutText - &sOutput[0]);

		return sOutput;
	}
};
