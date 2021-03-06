#pragma once

#include "Core.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // for logging custom types
#pragma warning(pop)

namespace ZZX 
{
    class Log
    {
    public:
        static void Init();

        inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define ZZX_CORE_ERROR(...) ::ZZX::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ZZX_CORE_WARN(...)  ::ZZX::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ZZX_CORE_INFO(...)  ::ZZX::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ZZX_CORE_TRACE(...) ::ZZX::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ZZX_CORE_CRITICAL(...) ::ZZX::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define ZZX_ERROR(...) ::ZZX::Log::GetClientLogger()->error(__VA_ARGS__)
#define ZZX_WARN(...)  ::ZZX::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ZZX_INFO(...)  ::ZZX::Log::GetClientLogger()->info(__VA_ARGS__)
#define ZZX_TRACE(...) ::ZZX::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ZZX_CRITICAL(...) ::ZZX::Log::GetClientLogger()->critical(__VA_ARGS__)
