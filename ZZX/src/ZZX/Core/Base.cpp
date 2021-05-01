#include "zzxpch.h"
#include "Base.h"
#include "Log.h"

#define ZZX_BUILD_ID "v0.1a"

namespace ZZX {

    void InitializeCore()
    {
        Log::Init();

        ZZX_CORE_TRACE("ZEngine {}", ZZX_BUILD_ID);
        ZZX_CORE_TRACE("Initializing...");
    }

    void ShutdownCore()
    {
        ZZX_CORE_TRACE("Shutting down...");

        Log::Shutdown();
    }
}
