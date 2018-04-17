// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "PlatformTypes.h"
#include <algorithm>
#include <iterator>

enum class FileFormat : unsigned short
{
	PLAIN_TEXT, // .txt
	MARKDOWN,   // .md
	CONSOLE     // raw output
};

enum ErrorCode
{
	SUCCESS = 0,
	INVALID_PATH,
	INVALID_MASK,
	INVALID_FIND_STRING,
	INVALID_INPUT_FILE,
	INVALID_ARGUMENTS
};