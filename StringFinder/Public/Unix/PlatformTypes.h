#ifndef _PLATFORMTYPES_H
#define _PLATFORMTYPES_H

// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

typedef std::string FString;               // Base string
typedef std::ostream FStream;              // Base ostream
typedef std::fstream FFile;                // Base file
typedef std::stringstream FStringStream;   // Base stringstream
typedef char FChar;                        // Base char

#define _S(text) text                      // Decorate string
#define COUT std::cout                     // Base cout

/* Platform specifiec utils */
class PlatformUtils
{
public:
    // Convert raw string into FString
    static inline FString StringFormat(const std::string& sIn) {
        return sIn;
    }
};


#endif // _PLATFORMTYPES_H
