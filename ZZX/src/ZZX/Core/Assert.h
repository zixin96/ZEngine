#pragma once

#ifdef ZZX_DEBUG
    #define ZZX_ENABLE_ASSERTS
#endif

#ifdef ZZX_ENABLE_ASSERTS
    #define ZZX_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { ZZX_ERROR("Assertion Failed"); __debugbreak(); } }
    #define ZZX_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { ZZX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

    #define ZZX_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
    #define ZZX_GET_ASSERT_MACRO(...) ZZX_EXPAND_VARGS(ZZX_ASSERT_RESOLVE(__VA_ARGS__, ZZX_ASSERT_MESSAGE, ZZX_ASSERT_NO_MESSAGE))

    #define ZZX_ASSERT(...) ZZX_EXPAND_VARGS( ZZX_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
    #define ZZX_CORE_ASSERT(...) ZZX_EXPAND_VARGS( ZZX_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#else
    #define ZZX_ASSERT(...)
    #define ZZX_CORE_ASSERT(...)
#endif
