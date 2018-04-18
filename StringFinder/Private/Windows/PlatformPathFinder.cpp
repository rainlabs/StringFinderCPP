// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "PlatformPathFinder.h"
#include <io.h>
#include <regex>
#include "Strings.h"

PlatformPathFinder::~PlatformPathFinder()
{
}

size_t PlatformPathFinder::Iterate(std::function<void(const FString&)> fFunction)
{
	size_t uCount(0);
	struct _wfinddata_t oFindData;
	FString sCurrentFolder(m_sPath);

	if (sCurrentFolder[sCurrentFolder.size() - 1] != _S('\\')) {
		sCurrentFolder += _S('\\');
	}

	intptr_t hFile = _wfindfirst((sCurrentFolder + _S("*")).c_str(), &oFindData);
	if (hFile == -1) return 0;

	FString sMaskInternal(m_sMask);
	if (m_sMask[0] == _S('*')) {
		sMaskInternal = _S(".") + m_sMask;
	}
	std::wregex rMask;

	// Check for valid to regex mask
	try {
		rMask = sMaskInternal;
	}
	catch (std::regex_error e) {
		Utils::WriteInConsole(STR_INCORRECT_MASK);
	}

	// Recursive iteration
	// TODO: for optimization find all files first and iterate over vector
	do {
		if (CheckValidName(oFindData.name, oFindData.attrib)) {
			FString sFullName = sCurrentFolder + oFindData.name;
			if (IsFolder(oFindData.attrib)) {
				PlatformPathFinder oSubFinder(sFullName, m_sMask, m_bIgnoreHidden);
				uCount += oSubFinder.Iterate(fFunction);
			}
			else if (std::regex_match(oFindData.name, rMask)) {
				fFunction(sFullName);
				uCount++;
			}
		}
	} while (_wfindnext(hFile, &oFindData) == 0);

	_findclose(hFile);
	return uCount;
}

PlatformPathFinder::PlatformPathFinder(const FString & sPath, const FString & sMask, bool bIgnoreHidden) :
	PathFinder(sPath, sMask, bIgnoreHidden),
	m_sPath(sPath),
	m_sMask(sMask),
	m_bIgnoreHidden(bIgnoreHidden)
{
}

bool PlatformPathFinder::CheckValidName(const FString & sName, unsigned int iAttrib)
{
	if (sName.empty()) return false;
	if (sName == _S(".")) return false;  // exclude current folder
	if (sName == _S("..")) return false; // exclude parent folder

	// Exclude hidden if needed
	if (m_bIgnoreHidden)
	{
		if (iAttrib & _A_HIDDEN) return false;
		if (sName[0] == _S('.')) return false;
	}

	return true;
}

bool PlatformPathFinder::IsFolder(unsigned int iAttrib)
{
	return iAttrib & _A_SUBDIR;
}
