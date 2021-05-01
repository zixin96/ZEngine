#include "zzxpch.h"
#include "ZZX/Core/Application.h"
#include "ZZX/Core/Log.h"
#include "ZZX/Core/Input.h"
#include "ZZX/Core/KeyCodes.h" // Application::onWindowKeyClosed

#include "ZZX/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

const static uint32_t WINDOW_WIDTH = 1600;
const static uint32_t WINDOW_HEIGHT = 900;

extern bool g_ApplicationRunning;

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
        ZE_PROFILE_FUNCTION();

        ZE_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = IWindow::Create(WindowProperties(name, WINDOW_WIDTH, WINDOW_HEIGHT));
        m_Window->SetEventCallback(ZE_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        m_ImguiLayer = new ImguiLayer();
        PushOverlay(m_ImguiLayer);
    }

    Application::~Application()
    {
        ZE_PROFILE_FUNCTION();

        Renderer::Shutdown();
    }

    void Application::PushLayer(Layer* layer)
    {
        ZE_PROFILE_FUNCTION();

        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        ZE_PROFILE_FUNCTION();

        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::Close()
    {
        m_Running = false;
    }

    void Application::Run()
    {
        ZE_PROFILE_FUNCTION();

        while (m_Running)
        {
            ZE_PROFILE_SCOPE("Application RunLoop");

            float time = (float)glfwGetTime(); // Platform::GetTime
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimized)
            {
                {
                    ZE_PROFILE_SCOPE("LayerStack - OnUpdate");
                    for (Layer* layer : m_LayerStack)
                    {
                        layer->OnUpdate(timestep);
                    }
                }
            }

            m_ImguiLayer->Begin();
            {
                ZE_PROFILE_SCOPE("LayerStack - OnImguiRender");
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
        ZE_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(ZE_BIND_EVENT_FN(Application::OnWindowClosed));
        dispatcher.Dispatch<KeyPressedEvent>(ZE_BIND_EVENT_FN(Application::OnWindowKeyPressed));
        dispatcher.Dispatch<WindowResizeEvent>(ZE_BIND_EVENT_FN(Application::OnWindowResized));

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
        m_Running = false;
        g_ApplicationRunning = false; // Request close
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
        ZE_PROFILE_FUNCTION();

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

