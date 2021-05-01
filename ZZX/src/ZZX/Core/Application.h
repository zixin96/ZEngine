#pragma once

#include "ZZX/Core/Base.h"
#include "ZZX/Core/IWindow.h"
#include "ZZX/Core/LayerStack.h"
#include "ZZX/Events/Event.h"
#include "ZZX/Events/ApplicationEvent.h"

#include "ZZX/Core/Timestep.h"
#include "ZZX/Imgui/ImguiLayer.h"

namespace ZE
{
    class Application
    {
    public: 
        Application(const std::string& name = "ZEngine");
        virtual ~Application();

        void Run();
        void Close();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        static Application& Get() { return *s_Instance; }

        IWindow& GetWindow() { return *m_Window; }

        ImguiLayer* GetImGuiLayer() { return m_ImguiLayer; }
    private:
        bool OnWindowClosed(WindowCloseEvent& e);
        bool OnWindowKeyPressed(KeyPressedEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        Scope<IWindow>      m_Window;
        ImguiLayer*         m_ImguiLayer;
        LayerStack          m_LayerStack; 
        float               m_LastFrameTime;
        bool                m_Running;
        bool                m_Minimized;

        static Application* s_Instance;
    };

    // to be defined in CLIENT
    Application* CreateApplication();
}


