#pragma once

#ifdef ZE_DEBUG
    #define ZE_ENABLE_ASSERTS
#endif

#ifdef ZE_ENABLE_ASSERTS
    #define ZE_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { ZE_ERROR("Assertion Failed"); __debugbreak(); } }
    #define ZE_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { ZE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

    #define ZE_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
    #define ZE_GET_ASSERT_MACRO(...) ZE_EXPAND_VARGS(ZE_ASSERT_RESOLVE(__VA_ARGS__, ZE_ASSERT_MESSAGE, ZE_ASSERT_NO_MESSAGE))

    #define ZE_ASSERT(...) ZE_EXPAND_VARGS( ZE_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
    #define ZE_CORE_ASSERT(...) ZE_EXPAND_VARGS( ZE_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#else
    #define ZE_ASSERT(...)
    #define ZE_CORE_ASSERT(...)
#endif
