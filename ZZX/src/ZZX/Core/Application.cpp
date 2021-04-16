#include "zzxpch.h"
#include "ZZX/Core/Application.h"
#include "ZZX/Core/Log.h"
#include "ZZX/Core/Input.h"
#include "ZZX/Core/KeyCodes.h" // Application::onWindowKeyClosed

#include "ZZX/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace ZZX
{
    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string& name)
        : m_Window(nullptr),
        m_ImguiLayer(nullptr),
        m_LayerStack(),
        m_LastFrameTime(0.0f),
        m_Running(true),
        m_Minimized(false)
    {
        ZZX_PROFILE_FUNCTION();

        ZZX_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = IWindow::Create(WindowProperties(name));
        m_Window->SetEventCallback(ZZX_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        m_ImguiLayer = new ImguiLayer();
        PushOverlay(m_ImguiLayer);
    }

    Application::~Application()
    {
        ZZX_PROFILE_FUNCTION();

        Renderer::Shutdown();
    }

    void Application::PushLayer(Layer* layer)
    {
        ZZX_PROFILE_FUNCTION();

        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        ZZX_PROFILE_FUNCTION();

        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::Close()
    {
        m_Running = false;
    }

    void Application::Run()
    {
        ZZX_PROFILE_FUNCTION();

        while (m_Running)
        {
            ZZX_PROFILE_SCOPE("Application RunLoop");

            float time = (float)glfwGetTime(); // Platform::GetTime
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimized)
            {
                {
                    ZZX_PROFILE_SCOPE("LayerStack - OnUpdate");
                    for (Layer* layer : m_LayerStack)
                    {
                        layer->OnUpdate(timestep);
                    }
                }
            }

            m_ImguiLayer->Begin();
            {
                ZZX_PROFILE_SCOPE("LayerStack - OnImguiRender");
                for (Layer* layer : m_LayerStack)
                {
                    layer->OnImguiRender();
                }
            }
            m_ImguiLayer->End();
            

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        ZZX_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(ZZX_BIND_EVENT_FN(Application::OnWindowClosed));
        dispatcher.Dispatch<KeyPressedEvent>(ZZX_BIND_EVENT_FN(Application::OnWindowKeyPressed));
        dispatcher.Dispatch<WindowResizeEvent>(ZZX_BIND_EVENT_FN(Application::OnWindowResized));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {            
            if (e.Handled)
            {
                break;
            }
            (*it)->OnEvent(e);
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent& e)
    {
        Close();
        return true;
    }

    bool Application::OnWindowKeyPressed(KeyPressedEvent& e)
    {
        if (Input::IsKeyPressed(Key::Escape))
        {
            Close();
            return true;
        }
        return false;
    }

    bool Application::OnWindowResized(WindowResizeEvent& e)
    {
        ZZX_PROFILE_FUNCTION();

        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }
        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        return false;
    }
}

