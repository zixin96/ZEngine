#include "zzxpch.h"
#include "Base.h"
#include "Log.h"

#define ZE_BUILD_ID "v0.1a"

namespace ZE {

    void InitializeCore()
    {
        Log::Init();

        ZE_CORE_TRACE("ZEngine {}", ZE_BUILD_ID);
        ZE_CORE_TRACE("Initializing...");
    }

    void ShutdownCore()
    {
        ZE_CORE_TRACE("Shutting down...");

        Log::Shutdown();
    }
}
