// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "PlatformPathFinder.h"
#include <sys/types.h>
#include <dirent.h>
#include "Strings.h"

#define INVALID_HANDLE_VALUE -1

PlatformPathFinder::~PlatformPathFinder()
{
}

size_t PlatformPathFinder::Iterate(std::function<void(const FString&)> fFunction)
{
	size_t uCount(0);
    struct dirent* pDirent;
	FString sCurrentFolder(m_sPath);

	if (sCurrentFolder[sCurrentFolder.size() - 1] != _S('\\')) {
		sCurrentFolder += _S('\\');
	}

    DIR* hDir = opendir(sCurrentFolder.c_str());
    if(hDir == nullptr)
        return 0;

	FString sMaskInternal(m_sMask);
	if (m_sMask[0] == _S('*')) {
		sMaskInternal = _S(".") + m_sMask;
	}

	// Check for valid to regex mask
    std::wregex rMask;
    try {
		rMask = sMaskInternal;
	}
	catch (std::regex_error e) {
		Utils::WriteInConsole(STR_INCORRECT_MASK);
	}

    while ((pDirent = readdir(hDir)) != nullptr) {
        if (!CheckValidName(pDirent->d_name, pDirent->d_type)) continue;

        FString sFullName = sCurrentFolder + pDirent->d_name;
        if (IsFolder(pDirent->d_type)) {
            PlatformPathFinder oSubFinder(sFullName, m_sMask, m_bIgnoreHidden);
            uCount += oSubFinder.Iterate(fFunction);
        }
        else if (std::regex_match(pDirent->d_name, rMask)) {
            fFunction(sFullName);
            uCount++;
        }
    }

    closedir(hDir);
	return uCount;
}

PlatformPathFinder::PlatformPathFinder(const FString & sPath, const FString & sMask, bool bIgnoreHidden) :
	PathFinder(sPath, sMask, bIgnoreHidden),
	m_sPath(sPath),
	m_sMask(sMask),
	m_bIgnoreHidden(bIgnoreHidden)
{
}

bool PlatformPathFinder::CheckValidName(const FString & sName, unsigned char cType)
{
	if (sName.empty()) return false;
    if (cType != DT_REG && cType != DT_DIR) return false;

	if (sName == _S(".")) return false;  // exclude current folder
	if (sName == _S("..")) return false; // exclude parent folder

	// Exclude hidden if needed
    if (m_bIgnoreHidden && sName[0] == _S('.')) return false;

	return true;
}

bool PlatformPathFinder::IsFolder(unsigned char cType)
{
    return cType == DT_DIR;
}
