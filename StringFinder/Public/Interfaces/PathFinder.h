// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "CommonTypes.h"
#include <functional>
#include <memory>

class PathFinder;
typedef std::shared_ptr<PathFinder> PathFinderPtr;

/* PathFinder interface */
class PathFinder
{
public:
	// Instanciate platform speciefic finder
	static PathFinderPtr CreateInstance(const FString& sPath, const FString& sMask, bool bIgnoreHidden = true);
	virtual ~PathFinder() {};

	// Iterate over all found files
	virtual size_t Iterate(std::function<void(const FString&)> fFunction) = 0;

protected:
	PathFinder(const FString & sPath, const FString & sMask, bool bIgnoreHidden) {};
};