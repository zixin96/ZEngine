#include "zzxpch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace ZZX
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        ZE_CORE_ASSERT(windowHandle, "Handle is null!");
    }

    void OpenGLContext::Init()
    {
        ZE_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ZE_CORE_ASSERT(status, "Fail to initialize GLAD!");

        ZE_CORE_INFO("OpenGL Info:");
        ZE_CORE_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
        ZE_CORE_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
        ZE_CORE_INFO(" Version: {0}", glGetString(GL_VERSION));
        #ifdef ZE_ENABLE_ASSERTS
            int versionMajor;
            int versionMinor;
            glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
            glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
            ZE_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "ZZX requires at least OpenGL version 4.5!");
        #endif
    }

    void OpenGLContext::SwapBuffers()
    {
        ZE_PROFILE_FUNCTION();

        glfwSwapBuffers(m_WindowHandle);
    }
}
