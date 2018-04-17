// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "PlatformPathFinder.h"
#include <io.h>
#include <regex>

#define INVALID_HANDLE_VALUE -1

PlatformPathFinder::~PlatformPathFinder()
{
}

size_t PlatformPathFinder::Iterate(std::function<void(const FString&)> fFunction)
{
	size_t uCount(0);
	struct _wfinddata_t oFindData;
	intptr_t hFile = _wfindfirst((m_sPath + _S("\\*")).c_str(), &oFindData);

	FString sMaskInternal(m_sMask);
	if (m_sMask[0] == _S('*')) {
		sMaskInternal = _S(".") + m_sMask;
	}
	std::wregex rMask(sMaskInternal);

	if (hFile == INVALID_HANDLE_VALUE) return 0;

	do {
		if (CheckValidName(oFindData.name, oFindData.attrib)) {
			FString sFullName = m_sPath + _S("\\") + oFindData.name;
			if (IsFolder(oFindData.attrib)) {
				PlatformPathFinder oSubFinder(sFullName, m_sMask, m_bIgnoreHidden);
				uCount += oSubFinder.Iterate(fFunction);
			}
			else if (std::regex_match(oFindData.name, rMask)) {
				fFunction(sFullName);
			}
		}
	} while (_wfindnext(hFile, &oFindData) == 0);

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
	if (sName == _S(".")) return false;
	if (sName == _S("..")) return false;

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
