#include "zzxpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace ZZX
{
    Ref<VertexArray> VertexArray::Create()
    {
        // which api are we using? 
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                ZE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLVertexArray>();
        }

        ZE_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }
}