#pragma once
#include <memory>
#include "ZZX/Core/PlatformDetection.h"

#ifdef ZZX_DEBUG
    #if defined(ZZX_PLATFORM_WINDOWS)
        #define ZZX_DEBUGBREAK() __debugbreak()
    #elif defined(ZZX_PLATFORM_LINUX)
        #include <signal.h>
        #define ZZX_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
        #define ZZX_ENABLE_ASSERTS
#else
    #define ZZX_DEBUGBREAK()
#endif

#define ZZX_EXPAND_MACRO(x) x
#define ZZX_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define ZZX_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); } 

namespace ZZX
{
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}

#include "ZZX/Core/Log.h"
#include "ZZX/Core/Assert.h"
