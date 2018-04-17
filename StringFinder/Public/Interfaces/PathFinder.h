// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "CommonTypes.h"
#include <functional>
#include <memory>

class PathFinder;
typedef std::shared_ptr<PathFinder> PathFinderPtr;

class PathFinder
{
public:
	static PathFinderPtr CreateInstance(const FString& sPath, const FString& sMask, bool bIgnoreHidden = true);
	virtual ~PathFinder() {};
	virtual size_t Iterate(std::function<void(const FString&)> fFunction) = 0;

protected:
	PathFinder(const FString & sPath, const FString & sMask, bool bIgnoreHidden) {};
};