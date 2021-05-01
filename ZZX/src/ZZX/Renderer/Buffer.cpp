#include "zzxpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace ZE
{

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size, float* vertices)
    {
        // which api are we using? 
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                ZE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLVertexBuffer>(size, vertices);
        }

        ZE_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        // which api are we using? 
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            ZE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(size);
        }

        ZE_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t count, uint32_t* indices)
    {
        // which api are we using? 
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            ZE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLIndexBuffer>(count, indices);
        }

        ZE_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }

}