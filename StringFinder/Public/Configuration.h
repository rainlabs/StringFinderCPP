// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "CommonTypes.h"

class Configuration
{
public:
	Configuration();
	Configuration(int argc, char * argv[]);
	~Configuration();

	// Parse parameters
	void Initialize(int argc, char * argv[]);

	/* Config Getters */
	FString GetPath() const;
	FString GetFileMask() const;
	FString GetFindString() const;
	FString GetOutputFile() const;
	FileFormat GetOutputFormat() const;
	// Enabled extended output (will write each found line with line number in output)
	bool IsExtendedOutput() const;
	// Show additional info at the end of performing
	bool ShowInfo() const;
	// Show usage help
	bool ShowHelp() const;
	// read file open mode
	int GetOpenMode() const;
	// Get Chunk count/mode
	int GetChunkCount() const;

	// Check all parameters is valid to proceed
	bool IsValid() const;

	// Output config for easy debug
	friend FStream & operator<<(FStream & oStream, const Configuration & oConfig);

protected:
	// Read "find string" from file
	FString ReadFindString(const FString & sFile) const;

private:
	FString m_sPath;         // Folder to search
	FString m_sFileMask;     // File mask
	FString m_sFindString;   // String to find
	FString m_sOutputFile;   // Output file if existed
	bool m_bOutputExtended;  // Flag: extended input enabled
	bool m_bValidOutputFile; // Valid or not output file
	bool m_bShowInfo;        // Show took time and files number
	bool m_bShowHelp;        // Show usave commands
	bool m_bBinaryFlag;      // Should Read binary files
	int  m_iChunkCount;      // chunk count for reading, 0 - line by line
};