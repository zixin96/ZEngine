#pragma once

#include "Base.h"
#include "spdlog/spdlog.h"

namespace ZZX 
{
    class Log
    {
    public:
        static void Init();
        static void Shutdown();

        inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define ZE_CORE_ERROR(...) ::ZZX::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ZE_CORE_WARN(...)  ::ZZX::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ZE_CORE_INFO(...)  ::ZZX::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ZE_CORE_TRACE(...) ::ZZX::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ZE_CORE_CRITICAL(...) ::ZZX::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define ZE_ERROR(...) ::ZZX::Log::GetClientLogger()->error(__VA_ARGS__)
#define ZE_WARN(...)  ::ZZX::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ZE_INFO(...)  ::ZZX::Log::GetClientLogger()->info(__VA_ARGS__)
#define ZE_TRACE(...) ::ZZX::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ZE_CRITICAL(...) ::ZZX::Log::GetClientLogger()->critical(__VA_ARGS__)
