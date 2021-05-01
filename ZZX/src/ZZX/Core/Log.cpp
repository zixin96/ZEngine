#include "zzxpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"  
#include "spdlog/sinks/basic_file_sink.h"
#include <filesystem>
 
namespace ZE
{
    Ref<spdlog::logger> Log::s_CoreLogger;
    Ref<spdlog::logger> Log::s_ClientLogger;

    void Log::Init()
    {
        // Create "logs" directory if doesn't exist
        std::string logsDirectory = "logs";
        if (!std::filesystem::exists(logsDirectory))
            std::filesystem::create_directories(logsDirectory);

        std::vector<spdlog::sink_ptr> zzxSinks =
        {
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
            std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/ZENGINE.log", true)
        };

        std::vector<spdlog::sink_ptr> appSinks =
        {
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
            std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/APP.log", true)
        };

        zzxSinks[0]->set_pattern("%^[%T] %n: %v%$");
        zzxSinks[1]->set_pattern("[%T] [%l] %n: %v");
        appSinks[0]->set_pattern("%^[%T] %n: %v%$");
        appSinks[1]->set_pattern("[%T] [%l] %n: %v");

        s_CoreLogger = std::make_shared<spdlog::logger>("ZENGINE", zzxSinks.begin(), zzxSinks.end());
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = std::make_shared<spdlog::logger>("APP", appSinks.begin(), appSinks.end());
        s_ClientLogger->set_level(spdlog::level::trace);
    }

    void Log::Shutdown()
    {
        s_ClientLogger.reset();
        s_CoreLogger.reset();
        spdlog::drop_all();
    }
}
