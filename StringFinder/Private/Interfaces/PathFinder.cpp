// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "PathFinder.h"
#include "PlatformPathFinder.h"

PathFinderPtr PathFinder::CreateInstance(const FString & sPath, const FString & sMask, bool bIgnoreHidden)
{
	return std::make_shared<PlatformPathFinder>(PlatformPathFinder(sPath, sMask, bIgnoreHidden));
}
