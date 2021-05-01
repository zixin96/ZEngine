#pragma once
// This header file will be included by client applications (EditorApp.cpp, Game.cpp, etc)
// so that client project can call this main entrypoint

#ifdef ZE_PLATFORM_WINDOWS

// To be defined in client
extern ZE::Application* ZE::CreateApplication();

bool g_ApplicationRunning = true;

int main(int argc, char** argv)
{
    while (g_ApplicationRunning)
    {
        ZE::InitializeCore();
        ZE::Application* app = ZE::CreateApplication();
        ZE_CORE_ASSERT(app, "Client Application is null!");
        app->Run();
        delete app;
        ZE::ShutdownCore();
    }
}

#endif