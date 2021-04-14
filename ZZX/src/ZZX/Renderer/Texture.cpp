#include "zzxpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"


namespace ZZX
{
    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        // which api are we using? 
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                ZZX_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture2D>(path);
        }

        ZZX_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        // which api are we using? 
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                ZZX_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture2D>(width, height);
        }

        ZZX_CORE_ASSERT(false, "Unknown RenderAPI!");
        return nullptr;
    }
}