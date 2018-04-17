// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

typedef std::wstring FString;
typedef std::wostream FStream;
typedef std::wfstream FFile;
typedef std::wstringstream FStringStream;
typedef wchar_t FChar;

#define _S(text) L ## text
#define COUT std::wcout

class PlatformUtils
{
public:
	static inline FString StringFormat(const std::string& sIn) {
		FString sOutput(sIn.size(), '\0');
		auto& f = std::use_facet<std::codecvt<FChar, char, std::mbstate_t>>(std::locale());
		std::mbstate_t mb = std::mbstate_t();

		const char* sFromText;
		wchar_t* sOutText;
		f.in(mb, &sIn[0], &sIn[sIn.size()], sFromText,
			&sOutput[0], &sOutput[sOutput.size()], sOutText);
		sOutput.resize(sOutText - &sOutput[0]);

		return sOutput;
	}
};
