#pragma once

#include "ZZX/Core/Core.h"
#include "ZZX/Events/Event.h"

namespace ZZX
{
    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(const std::string& title = "ZZX Engine",
            uint32_t width = 1600,
            uint32_t height = 900)
            : Title(title), Width(width), Height(height)
        {}
    };

    // Interface representing a desktop system based window
    class   IWindow
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~IWindow() = default;

        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        // return void* b/c we don't necessary only have glfw window
        virtual void* GetNativeWindow() const = 0;

        static Scope<IWindow> Create(const WindowProps& props = WindowProps());
    };
}
