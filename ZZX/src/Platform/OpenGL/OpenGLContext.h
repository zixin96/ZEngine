#pragma once
#include "ZZX/Renderer/RendererContext.h"

struct GLFWwindow;

namespace ZE
{
    class OpenGLContext : public RendererContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}