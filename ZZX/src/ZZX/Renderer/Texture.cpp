#include "zzxpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"


namespace ZE
{
    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        // which api are we using? 
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                ZE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture2D>(path);
        }

        ZE_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        // which api are we using? 
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                ZE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture2D>(width, height);
        }

        ZE_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }
}