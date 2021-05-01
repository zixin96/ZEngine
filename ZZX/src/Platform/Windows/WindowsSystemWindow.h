#pragma once

#include "ZZX/Core/IWindow.h"
#include "ZZX/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace ZE
{
    class WindowsSystemWindow : public IWindow
    {
    public:
        WindowsSystemWindow(const WindowProperties& props);
        virtual ~WindowsSystemWindow();

        void OnUpdate() override;

        inline uint32_t GetWidth() const override { return m_Data.Width; }
        inline uint32_t GetHeight() const override { return m_Data.Height; }

        // Window attributes
        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline virtual void* GetNativeWindow() const override { return m_Window; }

    private:
        virtual void Init(const WindowProperties& props);
        virtual void Shutdown();
    private:
        GLFWwindow* m_Window;
        GraphicsContext* m_Context;
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            // Event callback will be set to Application::OnEvent
            // when the window is first created
            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}
