// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#pragma once

#include "CommonTypes.h"
#include <chrono>
#include <functional>

/* Simple measuremnt block */
struct Measurement
{
	static float Measure(std::function<void()> fFunction);
};