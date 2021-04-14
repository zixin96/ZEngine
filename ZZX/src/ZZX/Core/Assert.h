#pragma once

#include "ZZX/Core/Core.h"
#include "ZZX/Core/Log.h"
#include <filesystem>

#ifdef ZZX_ENABLE_ASSERTS

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define ZZX_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { ZZX##type##ERROR(msg, __VA_ARGS__); ZZX_DEBUGBREAK(); } }
	#define ZZX_INTERNAL_ASSERT_WITH_MSG(type, check, ...) ZZX_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define ZZX_INTERNAL_ASSERT_NO_MSG(type, check) ZZX_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", ZZX_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define ZZX_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define ZZX_INTERNAL_ASSERT_GET_MACRO(...) ZZX_EXPAND_MACRO( ZZX_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, ZZX_INTERNAL_ASSERT_WITH_MSG, ZZX_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define ZZX_ASSERT(...) ZZX_EXPAND_MACRO( ZZX_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define ZZX_CORE_ASSERT(...) ZZX_EXPAND_MACRO( ZZX_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define ZZX_ASSERT(...)
	#define ZZX_CORE_ASSERT(...)
#endif
