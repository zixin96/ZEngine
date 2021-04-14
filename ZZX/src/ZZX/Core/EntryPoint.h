#pragma once

#ifdef ZZX_PLATFORM_WINDOWS

extern ZZX::Application* ZZX::CreateApplication();

int main(int argc, char** argv)
{
    ZZX::Log::Init();

    ZZX_PROFILE_BEGIN_SESSION("Startup", "ZZXProfile-Startup.json");
    auto app = ZZX::CreateApplication();
    ZZX_PROFILE_END_SESSION();

    ZZX_PROFILE_BEGIN_SESSION("Runtime", "ZZXProfile-Runtime.json");
    app->Run();
    ZZX_PROFILE_END_SESSION();

    ZZX_PROFILE_BEGIN_SESSION("Shutdown", "ZZXProfile-Shutdown.json");
    delete app;
    ZZX_PROFILE_END_SESSION();
}

#endif