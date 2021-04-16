#include "zzxpch.h"
#include "WindowsSystemWindow.h"

#include "ZZX/Events/ApplicationEvent.h"
#include "ZZX/Events/MouseEvent.h"
#include "ZZX/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace ZZX
{
    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* description)
    {
        ZZX_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }
    
    WindowsSystemWindow::WindowsSystemWindow(const WindowProperties& props)
    {
        ZZX_PROFILE_FUNCTION();

        Init(props);
    }

    WindowsSystemWindow::~WindowsSystemWindow()
    {
        ZZX_PROFILE_FUNCTION();

        Shutdown();
    }

    void WindowsSystemWindow::OnUpdate()
    {
        ZZX_PROFILE_FUNCTION();

        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void WindowsSystemWindow::SetVSync(bool enabled)
    {
        ZZX_PROFILE_FUNCTION();

        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else {
            glfwSwapInterval(0);
        }
        m_Data.VSync = enabled;
    }

    bool WindowsSystemWindow::IsVSync() const
    {
        return m_Data.VSync;
    }

    void WindowsSystemWindow::Init(const WindowProperties& props)
    {
        ZZX_PROFILE_FUNCTION();

        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        ZZX_CORE_INFO("Creating window {0}, ({1}, {2})", props.Title, props.Width, props.Height);

        if (s_GLFWWindowCount == 0)
        {
            ZZX_PROFILE_SCOPE("glfwInit");

            ZZX_CORE_INFO("Initializing GLFW");
            int success = glfwInit();
            ZZX_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        {
            ZZX_PROFILE_SCOPE("glfwCreateWindow");

            m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
            ++s_GLFWWindowCount;
        }
        
        
        m_Context = new OpenGLContext(m_Window);
        m_Context->Init();
      
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });


        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });
    }

    void WindowsSystemWindow::Shutdown()
    {
        ZZX_PROFILE_FUNCTION();

        glfwDestroyWindow(m_Window);

        if (--s_GLFWWindowCount == 0)
        {
            ZZX_CORE_INFO("Terminating GLFW");
            glfwTerminate();
        }
    }
}


