#pragma once

#include "ZZX/Core/PlatformDetection.h"

#ifdef ZZX_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <sstream>

#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

// Data structures
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "ZZX/Core/Core.h"

#include "ZZX/Core/Log.h"

#include "ZZX/Debug/Instrumentor.h"

#ifdef ZZX_PLATFORM_WINDOWS
	// Windows API
	#include <Windows.h>
#endif


