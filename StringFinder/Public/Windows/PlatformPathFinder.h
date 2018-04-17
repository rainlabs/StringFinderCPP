// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "PathFinder.h"

/* Windows specified Path finder */
class PlatformPathFinder : public PathFinder
{
public:
	virtual ~PlatformPathFinder();

	// Iterate over all found files
	virtual size_t Iterate(std::function<void(const FString&)> fFunction);

protected:
	friend class PathFinder;
	PlatformPathFinder(const FString & sPath, const FString & sMask, bool bIgnoreHidden);

	// Check filename and exclude .|.. folders and hidden if needed
	bool CheckValidName(const FString & sName, unsigned int iAttrib);

	// Check for folder
	bool IsFolder(unsigned int iAttrib);

private:
	FString m_sPath;
	FString m_sMask;
	bool m_bIgnoreHidden;

};