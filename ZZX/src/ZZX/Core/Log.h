#pragma once

#include "Base.h"
#include "spdlog/spdlog.h"

namespace ZE 
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
#define ZE_CORE_ERROR(...) ::ZE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ZE_CORE_WARN(...)  ::ZE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ZE_CORE_INFO(...)  ::ZE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ZE_CORE_TRACE(...) ::ZE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ZE_CORE_CRITICAL(...) ::ZE::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define ZE_ERROR(...) ::ZE::Log::GetClientLogger()->error(__VA_ARGS__)
#define ZE_WARN(...)  ::ZE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ZE_INFO(...)  ::ZE::Log::GetClientLogger()->info(__VA_ARGS__)
#define ZE_TRACE(...) ::ZE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ZE_CRITICAL(...) ::ZE::Log::GetClientLogger()->critical(__VA_ARGS__)
