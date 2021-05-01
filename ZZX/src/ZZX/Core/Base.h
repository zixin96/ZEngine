#pragma once
#include <memory>

// __VA_ARGS__ expansion to get past MSVC "bug"
#define ZE_EXPAND_VARGS(x) x

#define BIT(x) (1 << x)

#define ZE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); } 

#include "ZZX/Core/Assert.h"

namespace ZZX
{
    void InitializeCore();
    void ShutdownCore();

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

